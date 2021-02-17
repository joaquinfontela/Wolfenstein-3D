#ifndef __PLAYER_DIED_H__
#define __PLAYER_DIED_H__

#include "Notification.h"

class PlayerDied : public Notification {
 private:
  int playerID;

 public:
  PlayerDied(int playerID);
  void send(SocketWrapper& socket);
};

#endif
