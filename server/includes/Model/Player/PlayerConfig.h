#ifndef __PLAYER_CONFIG_H__
#define __PLAYER_CONFIG_H__
#include "../../../../common/includes/YAML/YAMLConfigReader.h"

typedef struct PlayerConfig{
  unsigned int MAX_HEALTH;
  unsigned int MAX_AMMO;
  unsigned int BULLET_DROP_WHEN_DIES;
  unsigned int AMMO_PICK_UP;
  unsigned int POINTS_PER_KILL;
  unsigned int AMMO_AT_START;
  unsigned int MAX_RESPAWN;

  PlayerConfig(YAMLConfigReader reader) : MAX_HEALTH(reader.getMaxHealth()),
                                          MAX_AMMO(reader.getMaxAmountOfBullets()),
                                          BULLET_DROP_WHEN_DIES(reader.getBulletAmountDropWhenPlayerDies()),
                                          AMMO_PICK_UP(reader.getBulletAmountWhenPickUpAmmo()),
                                          POINTS_PER_KILL(reader.getPointsPerKill()),
                                          AMMO_AT_START(reader.getBulletAmountAtStart()),
                                          MAX_RESPAWN(reader.getMaxReviveTimes()){}

}PlayerConfig;



#endif
