#ifndef __PLAYER_UPDATE_POSITION_H__
#define __PLAYER_UPDATE_POSITION_H__
#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"

class PlayerUpdatePosition : public Notification {
 private:
  int playerID;
  int newX, newY;

 public:
  PlayerUpdatePosition(int playerID, int x, int y);

  void send(SocketWrapper& socket);
};

#endif
