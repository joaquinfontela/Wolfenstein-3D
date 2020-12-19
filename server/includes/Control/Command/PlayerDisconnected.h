#ifndef __PLAYER_DISCONNECTED_H__
#define __PLAYER_DISCONNECTED_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerDisconnected : public Command {
 private:
  int playerID;


 public:
  PlayerDisconnected(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
