#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../common/includes/PlayerData.h"
#include "drawable.h"

class Player : public Drawable {
 public:
  Player(double posX, double posY, double dirX, double dirY, double planeX, double planeY, int id) :
  Drawable(posX, posY, 3) , dirX(dirX), dirY(dirY), planeX(planeX), planeY(planeY), playerID(id), health(100), lives(2) {}

  ~Player() {}
  Player(PlayerData& info);
  void update(PlayerData& info);
  void update(double posX, double posY, double dirX, double dirY);
  void draw(TextureManager& manager, double posX, double posY, double dirX,
    double dirY, double planeX, double planeY, double* zBuffer) override;
  int getSoldierId(double x, double y, double dirX, double dirY);
  double calculateDist(Player* other);

  int playerID;
  int weaponId;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
  int health;
  int lives;
};

#endif  // PLAYER_H_
