#include "../../../includes/Control/Notification/PlayerPackageUpdate.h"

#include "../../../../common/includes/protocol.h"

PlayerUpdatePosition::PlayerUpdatePosition(int playerID, int x, int y) {
  this->playerID = playerID;
  this->newX = x;
  this->newY = y;
}

void PlayerUpdatePosition::send(SocketCommunication& socket) {
  uint32_t opcode = PLAYER_POS_UPDATE;

  socket.send(&opcode, sizeof(opcode));

  uint32_t playerID = this->playerID;
  uint32_t x = this->newX;
  uint32_t y = this->newY;

  socket.send(&playerID, sizeof(playerID));
  socket.send(&x, sizeof(x));
  socket.send(&y, sizeof(y));
}
