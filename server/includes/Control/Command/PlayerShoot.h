#ifndef __PLAYER_SHOOT_H__
#define __PLAYER_SHOOT_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerShoot : public Command {
 private:
  int playerID;
  bool keyPressed;

 public:
  PlayerShoot(int playerID, bool keyPressed);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
