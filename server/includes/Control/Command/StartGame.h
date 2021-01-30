#ifndef __START_GAME_H__
#define __START_GAME_H__

#include "../Notification/Notification.h"
#include "Command.h"

class StartGame : public Command {
 private:
  int playerID;


 public:
  StartGame(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
