#include "../../../includes/Control/Notification/StartingMatch.h"

#include <iostream>

#include "../../../../common/includes/protocol.h"

void StartingMatch::send(SocketCommunication& socket) {
  uint32_t opcode = STARTING_MATCH;
  socket.send(&opcode, sizeof(opcode));
}
