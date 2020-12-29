#ifndef __PLAYER_AUP_H__
#define __PLAYER_AUP_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerAUp : public Command {
 private:
  int playerID;

 public:
  PlayerAUp(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
