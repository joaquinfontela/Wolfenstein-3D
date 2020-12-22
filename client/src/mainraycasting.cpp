#include <SDL2/SDL.h>
#include <math.h>

#include <climits>
#include <exception>
#include <iostream>

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

static double distanceBetweenPoints(double x1, double y1, double x2, double y2){
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}
static void renderWithPerspective(int x, int y, int viewAngle,
                                  SdlTexture* img1, SdlTexture* img2, SdlTexture* img3) {
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

  double distanceToProyection = floor((WIDTH / 2) / (tan((PI / 2) - PI / 3)));
  double testX = 384;
  double testY = 384;
  double posTable[WIDTH];



  AngleManager angles;

  double xBoxIntersection, yBoxIntersection;
  double dv, dh, dx, dy;
  double distanceOne = 0;
  double distanceTwo = 0;

  int xGrid, yGrid;
  int xIndex, yIndex;
  int alpha = viewAngle - angles.ANGLE30;

  if (alpha < 0) {
    alpha += angles.ANGLE360;
  }

  int initAlpha = alpha;

  int firstHit, secondHit;
  for (int i = 0; i < WIDTH; i++) {
    //std::cout << "Casting ray at angle: " << (alpha * 60) / WIDTH
            //  << " in column: " << i << std::endl;

    if (alpha > angles.ANGLE0 && alpha < angles.ANGLE180) {
      yGrid = floor(y / 64) * 64 + 64;
      dh = 64;
      xBoxIntersection = angles.fITanTable[alpha] * (yGrid - y) + x;
    } else {
      yGrid = floor(y / 64) * 64 - 1;
      dh = -64;
      xBoxIntersection = angles.fITanTable[alpha] * (yGrid - y) + x;
    }

    if (alpha == angles.ANGLE0 || alpha == angles.ANGLE180) {
      distanceTwo = INT_MAX;
    } else {
      dx = angles.fXStepTable[alpha];
      while (true) {
        xIndex = floor(xBoxIntersection / 64);
        yIndex = floor(yGrid / 64);


        if (xIndex >= DIMX || yIndex >= DIMY || xIndex < 0 || yIndex < 0) {
          distanceTwo = INT_MAX;
          break;
        } else if (matrix[xIndex][yIndex] != 0) {
          secondHit = matrix[xIndex][yIndex];
          distanceTwo = abs(xBoxIntersection - x) * abs(angles.fICosTable[alpha]);
          break;
        }else {
          xBoxIntersection += dx;
          yGrid += dh;
        }
      }
    }

    if (alpha < angles.ANGLE90 || alpha > angles.ANGLE270) {
      xGrid = floor(x / 64) * 64 + 64;
      dv = 64;
      yBoxIntersection = angles.fTanTable[alpha] * (xGrid - x) + y;
    } else {
      xGrid = floor(x / 64) * 64 - 1;
      dv = -64;
      yBoxIntersection = angles.fTanTable[alpha] * (xGrid - x) + y;
    }
    if (alpha == angles.ANGLE90 || alpha == angles.ANGLE270) {
      distanceOne = INT_MAX;
    } else {
      dy = angles.fYStepTable[alpha];
      while (true) {
        xIndex = floor(xGrid / 64);
        yIndex = floor(yBoxIntersection / 64);

        if (xIndex >= DIMX || yIndex >= DIMY || xIndex < 0 || yIndex < 0) {
          distanceOne = INT_MAX;
          break;
        } else if (matrix[xIndex][yIndex] != 0) {
          firstHit = matrix[xIndex][yIndex];
          distanceOne =
              abs(yBoxIntersection - y) * abs(angles.fISinTable[alpha]);
          break;
        } else {
          yBoxIntersection += dy;
          xGrid += dv;
        }
      }
    }

    double distanceToWall =
        (distanceOne > distanceTwo) ? distanceTwo : distanceOne;

    double wallHeight = (64.0 / distanceToWall) * distanceToProyection;
    wallHeight *= angles.fFishTable[i];

    int offset;
    int offset2;
    int textureToUse;
    if (distanceOne > distanceTwo) {
      textureToUse = secondHit;
      distanceToWall = distanceTwo;
      offset = (int)xBoxIntersection % 64;

    } else {
      textureToUse = firstHit;
      distanceToWall = distanceOne;
      offset = (int)yBoxIntersection % 64;

    }

    int height = ceil(wallHeight);
    Area destArea(i, (HEIGHT - height) / 2, 1, height);
    if (textureToUse == 1){
      Area srcArea(offset, 0, 1, height);
      img1->render(srcArea, destArea);
    } else{
      Area srcArea(offset, 0, 1, height);
      img2->render(srcArea, destArea);
    }

    posTable[i] = distanceToWall;
    alpha += 1;
    while (alpha >= angles.ANGLE360) alpha -= angles.ANGLE360;
  }

   double diffX = testX - x;
   double diffY = testY - y;
   double anguloJugadorObjeto = atan2(diffY, diffX) * 180/3.14159265359;
   double angleBetween = ((viewAngle  * 60/WIDTH) - (anguloJugadorObjeto));

   int angleBetweenColumnar = abs(((atan2(diffY, diffX) * 180/3.1415) * WIDTH/60));
   double distanceToPlayer = distanceBetweenPoints(x, y, testX, testY) * angles.fFishTable[angleBetweenColumnar];

   std::cout<<"Angle between: "<<angleBetween<<std::endl;
   if(angleBetweenColumnar < angles.ANGLE30){


     int spriteWidth = 168;
     int spriteHeight = ceil((64 / distanceToPlayer) * distanceToProyection);
     int columnDisplacement = (tan(atan2(diffY, diffX))) * distanceToPlayer;


     double angleDifference = abs((atan2(diffY, diffX) * 180/3.14159265359) - (viewAngle * 60/WIDTH));

     //int iterationRequired = angleDifference / (0.075);
     //std::cout<<iterationRequired<<std::endl;

     spriteWidth = spriteHeight;

     //columnDisplacement = iterationRequired;
     //std::cout<<"Column Displacement: "<<columnDisplacement<<std::endl;
     for(int i = 0; i < spriteWidth; i++){

       //std::cout<<"Wall distance: "<<posTable[columnDisplacement]<<" ,Sprite Distance: "<<distanceToPlayer<<std::endl;
       if(posTable[columnDisplacement + i] > distanceToPlayer){

         Area destArea(columnDisplacement + i, (HEIGHT - spriteHeight) / 2, 1, spriteHeight);
         Area srcArea(i, 0, 1, spriteHeight);
         img3->render(srcArea, destArea);
       }

     }
   }

   /*

   if(diferenciaAngulo < -3.14159){
     diferenciaAngulo += 2.0 * 3.14159;
   }
   if(diferenciaAngulo > 3.14159){
     diferenciaAngulo -= 2.0 * 3.14159;
   }

   diferenciaAngulo = abs(diferenciaAngulo);

   if(diferenciaAngulo < 3.14159265359/6){
     int altoTile = 64;

     double distanceToPlayer = distanceBetweenPoints(testX, testY, x, y);
     int alturaSprite = ((altoTile) / distanceToPlayer) * distanceToProyection;
     std::cout<<"Altura Sprite: "<<alturaSprite<<std::endl;

     int y0 = HEIGHT/2 - alturaSprite/2;
     int y1 = y0 + alturaSprite;

     std::cout<<y0<<std::endl<<y1<<std::endl;

     int alturaTextura = y1 + y0;
     int anchuraTextura = alturaTextura;

     int altoTextura = 64;
     int anchoTextura = 64;

     int dx = testX - x;
     int dy = testY - y;

     double spriteAngle = atan2(dy, dx) - ((viewAngle * 60/WIDTH) * 3.14159265359/180);

     int viewDist = HEIGHT;

     int x0 = tan(spriteAngle) * viewDist;

     int x2 = WIDTH/2 + x0 - anchuraTextura/2;

     int anchuraColumna = alturaTextura / altoTextura;

     std::cout<<"Anchura Columna: "<<anchuraColumna<<std::endl;

       // Hasta el ancho de la textura
     for (int i = 0; i < 168; i++) {
        for (int j = 0; j < anchuraColumna; j++) {
          int x1 = x2 + ((i - 1) * anchuraColumna) + j;

          if (posTable[x1] > distanceToPlayer) {
            Area srcArea(i, 0, 1, alturaTextura);
            Area destArea(x1, y1, 1, altoTextura - 1);

            std::cout<<"alturaTextura: "<<alturaTextura<<" altoTextura: "<<altoTextura<<std::endl;
            img3->render(srcArea, destArea);
          }
           //std::cout<<"Distancia a pared: "<<posTable[x1]<<", distancia a Jugador: "<<distanceToPlayer<<std::endl;
        }
      }


   }
*/





}

int main(int argc, char** argv) {

  int exitcode = 0;
  try {
    SdlWindow window(WIDTH, HEIGHT);
    SdlTexture im1(IMG_PATH "wall.png", window);
    SdlTexture im2(IMG_PATH "wall2.png", window);
    SdlTexture gun(IMG_PATH "chaingun2.png", window);
    SdlTexture back(IMG_PATH "hud.png", window);
    SdlTexture guard(IMG_PATH "guard.png", window);

    int y = 370;
    int x = 370;
    int deltax = 0;
    int deltay = 0;
    int xmouse = 0;
    AngleManager angles;

    double viewAngle = angles.ANGLE180;

    while (true) {
      SDL_Event event;
      window.fillWolfenstein();
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        break;
      } else if (event.type == SDL_KEYDOWN) {
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
        switch (key.keysym.sym) {
          case SDLK_a:
            if (x + 10 < DIMX * 64) deltax = 10;
            break;
          case SDLK_d:
            if (x - 10 > 0) deltax = -10;
            break;
          case SDLK_w:
            if (y + 10 < DIMY * 64) deltay = 10;
            break;
          case SDLK_s:
            if (y - 10 > 0) deltay = -10;
            break;
          case SDLK_LEFT:
            viewAngle -= angles.ANGLE10;
            if (viewAngle < 0) viewAngle += angles.ANGLE360;
            break;
          case SDLK_RIGHT:
            viewAngle += angles.ANGLE10;
            if (viewAngle > angles.ANGLE360) viewAngle -= angles.ANGLE360;
            break;
        }
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        window.playOrStopAudio();
      } else if (event.type == SDL_MOUSEMOTION) {
        if (event.motion.x > xmouse) {
          viewAngle += angles.ANGLE1p5;
          if (viewAngle > angles.ANGLE360) viewAngle -= angles.ANGLE360;
        } else {
          viewAngle -= angles.ANGLE1p5;
          if (viewAngle < 0) viewAngle += angles.ANGLE360;
        }
        xmouse = event.motion.x;
      }

      double theta = viewAngle - angles.ANGLE270;
      if (theta < 0) theta += angles.ANGLE360;
      if (theta > angles.ANGLE360) theta -= angles.ANGLE360;
      x -= deltax * angles.fCos(theta) - deltay * angles.fSin(theta);
      y -= deltax * angles.fSin(theta) + deltay * angles.fCos(theta);
      deltax = 0;  // Rotation matrix ^^^
      deltay = 0;

      renderWithPerspective(x, y, viewAngle, &im1, &im2, &guard);
      back.renderAll({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT});
      gun.renderAll({.x = WIDTH/2 - 130, .y = HEIGHT/2 - 78, .w = 250, .h = 250});
      window.render();
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    exitcode = 1;;
  }
  return exitcode;
}
