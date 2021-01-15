#ifndef __PLAYER_SWITCH_WEAPON_H__
#define __PLAYER_SWITCH_WEAPON_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerSwitchWeapon : public Command {
 private:
  int playerID;
  int weaponPos;

 public:
  PlayerSwitchWeapon(int playerID, int weaponPos);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
