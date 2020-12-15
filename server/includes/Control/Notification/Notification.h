#ifndef __NOTIFICATION_H__
#define __NOTIFICATION_H__
#include "../../../../common/includes/Socket/SocketCommunication.h"

class Notification {
 public:
  virtual void send(SocketCommunication& socket) = 0;
  ~Notification(){};
};

#endif