#ifndef __PLAYER_SDOWN_H__
#define __PLAYER_SDOWN_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerSDown : public Command {
 private:
  int playerID;

 public:
  PlayerSDown(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
