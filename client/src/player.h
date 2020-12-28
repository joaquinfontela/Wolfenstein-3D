#ifndef PLAYER_H_
#define PLAYER_H_

#include "drawable.h"

class Player : public Drawable {
 public:
  Player(double posX, double posY, double dirX, double dirY, double planeX, double planeY, int id) : Drawable(posX, posY, id) , posX(posX), posY(posY), dirX(dirX), dirY(dirY), planeX(planeX), planeY(planeY) {}
  double posX;
  double posY;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
  int id;
};

#endif  // PLAYER_H_
