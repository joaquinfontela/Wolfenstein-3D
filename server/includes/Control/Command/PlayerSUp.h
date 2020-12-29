#ifndef __PLAYER_SUP_H__
#define __PLAYER_SUP_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerSUp : public Command {
 private:
  int playerID;

 public:
  PlayerSUp(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
