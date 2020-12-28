#ifndef __PLAYER_DDOWN_H__
#define __PLAYER_DDOWN_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerDDown : public Command {
 private:
  int playerID;

 public:
  PlayerDDown(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
