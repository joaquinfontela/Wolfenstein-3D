#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../common/includes/PlayerData.h"
#include "drawable.h"

class Player : public Drawable {
 public:
  Player(PlayerData& info);
  void update(PlayerData& info);
  void update(double posX, double posY, double dirX, double dirY);
  Player(double posX, double posY, double dirX, double dirY, double planeX, double planeY, int id) :
  Drawable(posX, posY, 3) , dirX(dirX), dirY(dirY), planeX(planeX), planeY(planeY), playerID(id) {}
  void draw(TextureManager& manager, double posX, double posY, double dirX, double dirY, double planeX, double planeY, double* zBuffer);

  int playerID;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
};

#endif  // PLAYER_H_
