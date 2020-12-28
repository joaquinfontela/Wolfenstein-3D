#ifndef __PLAYER_ADOWN_H__
#define __PLAYER_ADOWN_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerADown : public Command {
 private:
  int playerID;

 public:
  PlayerADown(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
