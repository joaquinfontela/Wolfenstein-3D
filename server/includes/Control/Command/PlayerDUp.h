#ifndef __PLAYER_DUP_H__
#define __PLAYER_DUP_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerDUp : public Command {
 private:
  int playerID;

 public:
  PlayerDUp(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
