#include "../../../includes/Control/Notification/ElementSwitchPosition.h"
#include "../../../../common/includes/Socket/SocketWrapper.h"

#include "../../../../common/includes/protocol.h"

ElementSwitchPosition::ElementSwitchPosition(int uniqueId, double x, double y) {
  this->uniqueId = uniqueId;
  this->newX = x;
  this->newY = y;
}

void ElementSwitchPosition::send(SocketCommunication& socket) {
  uint32_t opcode = ELEMENT_SWITCH_POSITION;

  socket.send(&opcode, sizeof(opcode));

  uint32_t uniqueId = this->uniqueId;
  socket.send(&uniqueId, sizeof(uniqueId));

  SocketWrapper wrapper(socket);
  wrapper.send(this->newX);
  wrapper.send(this->newY);

}
