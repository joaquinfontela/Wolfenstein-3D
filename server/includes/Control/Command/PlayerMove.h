#ifndef __PLAYER_MOVE_H__
#define __PLAYER_MOVE_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerMove : public Command {
 private:
  int playerID;
  int x, y;

 public:
  PlayerMove(int playerID, int x, int y);
  void execute(NullPtrQueue<Notification*>& notifications);
};

#endif