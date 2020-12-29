#ifndef __PLAYER_WUP_H__
#define __PLAYER_WUP_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerWUp : public Command {
 private:
  int playerID;

 public:
  PlayerWUp(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
