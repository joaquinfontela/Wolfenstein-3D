#include <SDL2/SDL.h>
#include <math.h>

#include <climits>
#include <exception>
#include <iostream>
#include <time.h>

#include "anglemanager.h"
#include "sdltexture.h"
#include "sdlwindow.h"

#define EPSILON 0.0001
#define PI 3.14159265359
#define HEIGHT 600
#define WIDTH 800
#define IMG_PATH "../media/"
#define DIMX 12
#define DIMY 12




static void renderWithPerspective(double posX, double posY, double dirX, double dirY, double planeX, double planeY, SdlTexture* img1, int matrix[DIMX][DIMY], SdlTexture* img2, SdlTexture* img3){

  double naziX = 6;
  double naziY = 4;
  double zBuffer[WIDTH];
  for(int x = 0; x < WIDTH; x++){

    //calculate ray position and direction
   double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
   double rayDirX = dirX + planeX * cameraX;
   double rayDirY = dirY + planeY * cameraX;



   //which box of the map we're in
   int mapX = int(posX);
   int mapY = int(posY);

   //length of ray from current position to next x or y-side
   double sideDistX;
   double sideDistY;

    //length of ray from one x or y-side to next x or y-side
   double deltaDistX = std::abs(1 / rayDirX);
   double deltaDistY = std::abs(1 / rayDirY);
   double perpWallDist;

   //what direction to step in x or y-direction (either +1 or -1)
   int stepX;
   int stepY;

   int hit = 0; //was there a wall hit?
   int side; //was a NS or a EW wall hit?
   //calculate step and initial sideDist
   if(rayDirX < 0)
   {
     stepX = -1;
     sideDistX = (posX - mapX) * deltaDistX;
   }
   else
   {
     stepX = 1;
     sideDistX = (mapX + 1.0 - posX) * deltaDistX;
   }
   if(rayDirY < 0)
   {
     stepY = -1;
     sideDistY = (posY - mapY) * deltaDistY;
   }
   else
   {
     stepY = 1;
     sideDistY = (mapY + 1.0 - posY) * deltaDistY;
   }
   //perform DDA
   while (hit == 0)
   {
     //jump to next map square, OR in x-direction, OR in y-direction
     if(sideDistX < sideDistY)
     {
       sideDistX += deltaDistX;
       mapX += stepX;
       side = 0;
     }
     else
     {
       sideDistY += deltaDistY;
       mapY += stepY;
       side = 1;
     }

     if(mapX >= DIMX || mapY >= DIMY || mapX < 0 || mapX < 0){
       mapX = INT_MAX;
       mapY = INT_MAX;
     }

     //Check if ray has hit a wall
     if(matrix[mapX][mapY] > 0) hit = 1;
   }
   //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
   if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
   else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;


   int lineHeight = (int) (HEIGHT/ perpWallDist);
   int offset = 0;


  int texNum = matrix[mapX][mapY];

      //calculate value of wallX
  double wallX; //where exactly the wall was hit
  if (side == 0) wallX = posY + perpWallDist * rayDirY;
  else           wallX = posX + perpWallDist * rayDirX;
  wallX -= floor((wallX));

      //x coordinate on the texture
  int texX = int(wallX * double(64));
  if(side == 0 && rayDirX > 0) texX = 64 - texX - 1;
  if(side == 1 && rayDirY < 0) texX = 64 - texX - 1;

   if(side == 0)
      offset = int(sideDistX) % 64;
   else
      offset = int(sideDistY) % 64;
   Area destArea(x, (HEIGHT - lineHeight) / 2, 1, lineHeight);

   Area srcArea(texX, 0, 1, lineHeight);

   if(texNum == 1)
    img1->render(srcArea, destArea);
   else
    img2->render(srcArea, destArea);


  zBuffer[x] = perpWallDist;
}


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



}

int main(int argc, char** argv) {

  int matrix[DIMX][DIMY] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                            {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
                            {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
                            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
                            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int exitcode = 0;
    SdlWindow window(WIDTH, HEIGHT);
    SdlTexture im1(IMG_PATH "wall.png", window);
    SdlTexture im2(IMG_PATH "wall2.png", window);
    SdlTexture gun(IMG_PATH "chaingun2.png", window);
    SdlTexture back(IMG_PATH "hud.png", window);
    SdlTexture guard(IMG_PATH "guard.png", window);

    double posX = 6, posY = 4;  //x and y start position
    double dirX = -1, dirY = 0; //initial direction vector
    double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

    double oldDirX = 0;
    double oldPlaneX = 0;
    while (true) {
      SDL_Event event;
      window.fillWolfenstein();
      renderWithPerspective(posX, posY, dirX, dirY, planeX, planeY, &im1, matrix, &im2, &im2);
      back.renderAll({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT});
      gun.renderAll({.x = WIDTH/2 - 130, .y = HEIGHT/2 - 78, .w = 250, .h = 250});
      window.render();


      double moveSpeed = 0.25;
      double rotSpeed = 0.3;


      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        break;
      } else if (event.type == SDL_KEYDOWN) {
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
        switch (key.keysym.sym) {
          case SDLK_w:
            if(matrix[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
            if(matrix[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
            break;
          case SDLK_d:
            oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
            break;
          case SDLK_a:
            oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
            break;
          case SDLK_s:
            if(matrix[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
            if(matrix[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
            break;
          case SDLK_LEFT:
            break;
          case SDLK_RIGHT:
            break;
        }



      //back.renderAll({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT});
      //gun.renderAll({.x = WIDTH/2 - 130, .y = HEIGHT/2 - 78, .w = 250, .h = 250});

    }



  }
  return exitcode;
}
