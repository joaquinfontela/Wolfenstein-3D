#ifndef __DOOR_MOVING_H__
#define __DOOR_MOVING_H__
#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"

class DoorMoving : public Notification {
 private:
  int x, y;

 public:
  DoorMoving(int x, int y);

  void send(SocketWrapper& socket);
};

#endif
