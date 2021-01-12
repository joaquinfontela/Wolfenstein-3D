#ifndef __PLAYER_INTERACTDOOR_H__
#define __PLAYER_INTERACTDOOR_H__

#include "../Notification/Notification.h"
#include "Command.h"

class PlayerInteractDoor : public Command {
 private:
  int playerID;


 public:
  PlayerInteractDoor(int playerID);
  void execute(WaitingQueue<Notification*>& notifications, Game& game);
};

#endif
