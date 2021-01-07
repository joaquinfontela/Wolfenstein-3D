#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__

typedef struct PlayerData{
  unsigned int playerID;
  double posX, posY;
  double dirX, dirY;
  int weaponID;
  double rotSpeed;
  int health;
  int lives;
}PlayerData;

#endif
