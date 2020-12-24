#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdint>

class Player {

public:

  double dirX;
  double dirY;
  double posX;
  double posY;
  double planeX;
  double planeY;

  Player(double posX, double posY, double dirX, double dirY) : posX(posX), posY(posY), dirX(dirX), dirY(dirY), planeX(0), planeY(0.66){}

};

#endif  // PLAYER_H_
