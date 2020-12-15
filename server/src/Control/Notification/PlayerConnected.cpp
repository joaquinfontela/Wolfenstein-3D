#include "../../../includes/Control/Notification/PlayerConnected.h"

#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "../../../../common/includes/protocol.h"

PlayerConnected::PlayerConnected(int playerID, int x, int y) {
  this->playerID = playerID;
  this->x = x;
  this->y = y;
}

void PlayerConnected::send(SocketCommunication& socket) {
  uint32_t opcode = CONNECTED_OK;
  socket.send(&opcode, sizeof(opcode));

  uint32_t ID = this->playerID;

  socket.send(&ID, sizeof(ID));

  uint32_t x = this->x;
  uint32_t y = this->y;

  socket.send(&x, sizeof(x));
  socket.send(&y, sizeof(y));
}