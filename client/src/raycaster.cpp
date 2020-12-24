#include "raycaster.h"



void Raycaster::run(){

  while(alive){


    double dirX = self->dirX;
    double dirY = self->dirY;
    double posX = self->posX;
    double posY = self->posY;
    double planeX = self->planeX;
    double planeY = self->planeY;


    double zBuffer[this->width];
    for(int x = 0; x < this->width; x++){


       double cameraX = 2 * x / (double)this->width - 1;
       double rayDirX = dirX + planeX * cameraX;
       double rayDirY = dirY + planeY * cameraX;

       int mapX = int(posX);
       int mapY = int(posY);

       double sideDistX;
       double sideDistY;

       double deltaDistX = std::abs(1 / rayDirX);
       double deltaDistY = std::abs(1 / rayDirY);
       double perpWallDist;

       int stepX;
       int stepY;

       int hit = 0;
       int side;

       if(rayDirX < 0){
         stepX = -1;
         sideDistX = (posX - mapX) * deltaDistX;
       }
       else{
         stepX = 1;
         sideDistX = (mapX + 1.0 - posX) * deltaDistX;
       }
       if(rayDirY < 0){
         stepY = -1;
         sideDistY = (posY - mapY) * deltaDistY;
       }
       else{
         stepY = 1;
         sideDistY = (mapY + 1.0 - posY) * deltaDistY;
       }

       while (hit == 0){
         if(sideDistX < sideDistY){
           sideDistX += deltaDistX;
           mapX += stepX;
           side = 0;
         }
         else{
           sideDistY += deltaDistY;
           mapY += stepY;
           side = 1;
         }

         if(mapX >= matrix.dimx || mapY >= matrix.dimy || mapX < 0 || mapX < 0){
           mapX = INT_MAX;
           mapY = INT_MAX;
         }


         if(matrix[mapX][mapY] > 0) hit = 1;
       }

       if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
       else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;


       int lineHeight = (int) (this->height/ perpWallDist);
       int offset = 0;


      int texNum = matrix[mapX][mapY];


      double wallX;
      if (side == 0) wallX = posY + perpWallDist * rayDirY;
      else           wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));


      int texX = int(wallX * double(64));
      if(side == 0 && rayDirX > 0) texX = 64 - texX - 1;
      if(side == 1 && rayDirY < 0) texX = 64 - texX - 1;

       if(side == 0)
          offset = int(sideDistX) % 64;
       else
          offset = int(sideDistY) % 64;
       Area destArea(x, (this->height - lineHeight) / 2, 1, lineHeight);

       Area srcArea(texX, 0, 1, lineHeight);

       if(texNum == 1)
        img1->render(srcArea, destArea);
       else
        img2->render(srcArea, destArea);


      zBuffer[x] = perpWallDist;
      }

    /*
      // Sprite Casting

      double spriteX = naziX - posX;
      double spriteY = naziY - posY;


      double invDet = 1.0 / (planeX * dirY - dirX * planeY);

      double transformX = invDet * (dirY * spriteX - dirX * spriteY);
      double transformY = invDet * (-planeY * spriteX + planeX * spriteY);

      int spriteScreenX = int((WIDTH / 2) * (1 + transformX / transformY));

      int spriteHeight = abs(int(HEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye

      int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + HEIGHT / 2;
      if(drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

      int spriteWidth = abs( int (HEIGHT / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= WIDTH) drawEndX = WIDTH - 1;

      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
          {
            int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;

            if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < zBuffer[stripe]){
                Area srcArea(texX, 1, 1, spriteHeight);
                Area destArea(stripe, (HEIGHT - spriteHeight) / 2, 1, spriteHeight);
                img3->render(srcArea, destArea);

              }
            }

    */

}

}
