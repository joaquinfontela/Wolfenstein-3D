#ifndef __PLAYER_WDOWN_H__
#define __PLAYER_WDOWN_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerWDown : public Command {
 private:
  int playerID;

 public:
  PlayerWDown(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
