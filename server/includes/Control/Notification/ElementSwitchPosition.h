#ifndef __ELEMENT_SWITCH_POSITION_H__
#define __ELEMENT_SWITCH_POSITION_H__
#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"

class ElementSwitchPosition : public Notification {
 private:
  int uniqueId;
  double newX, newY;

 public:
  ElementSwitchPosition(int uniqueId, double x, double y);

  void send(SocketWrapper& socket);
};

#endif
