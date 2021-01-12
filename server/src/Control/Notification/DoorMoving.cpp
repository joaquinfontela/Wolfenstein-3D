#include "../../../includes/Control/Notification/DoorMoving.h"

#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "../../../../common/includes/protocol.h"

DoorMoving::DoorMoving(int x, int y) {
  this->x = x;
  this->y = y;
}

void DoorMoving::send(SocketCommunication& socket) {
  uint32_t opcode = OPEN_DOOR;
  socket.send(&opcode, sizeof(opcode));

  uint32_t x = this->x;
  uint32_t y = this->y;

  socket.send(&x, sizeof(x));
  socket.send(&y, sizeof(y));
}
