#ifndef __MISSILE_EXPLOTION_H__
#define __MISSILE_EXPLOTION_H__

#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"

class MissileExplotion : public Notification {
 private:
   int uniqueId;

 public:
  MissileExplotion(int uniqueId);

  void send(SocketWrapper& socket);
};

#endif
