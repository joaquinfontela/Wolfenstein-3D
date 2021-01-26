#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../common/includes/PlayerData.h"
#include "drawable.h"

class Player : public Drawable {
 public:
  Player(double posX, double posY, double dirX, double dirY, double planeX, double planeY, int id) :
  Drawable(posX, posY, 3, id) , shooting(false), dirX(dirX), dirY(dirY), planeX(planeX), planeY(planeY),
  playerID(id), health(100), lives(2), moving(false), bullets(8), hasTheKey(false), healthdown(false) {}

  ~Player() {}
  Player(PlayerData& info);
  void update(PlayerData& info);
  void update(double posX, double posY, double dirX, double dirY);
  void draw(TextureManager& manager, double posX, double posY, double dirX,
    double dirY, double planeX, double planeY, double* zBuffer, float diff) override;
  int getSoldierId(double x, double y, double dirX, double dirY);
  double calculateDist(Player* other);
  double calculateDist(int otherx, int othery);
  void startShooting();
  void stopShooting();
  bool isShooting();
  bool isMoving();
  void stopMoving();
  bool hasThisUniqueId(int otherid) override;
  bool isSprite() override;
  bool hasKey();

  int playerID;
  int weaponId;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
  int health;
  int lives;
  int bullets;
  int score;
  bool moving;
  int healthdown;
  bool key;

 private: // ¡HACER QUE LOS ATRIBUTOS SEAN PRIVADOS Y ARMAR GETTERS!
  bool hasTheKey;
  Area srcArea, destArea;
  bool shooting;
};

#endif  // PLAYER_H_
