#include "../../../includes/Control/Notification/PlayerDisconnect.h"

#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "../../../../common/includes/protocol.h"
PlayerDisconnect::PlayerDisconnect(int playerID) { this->playerID = playerID; }

void PlayerDisconnect::send(SocketCommunication& socket) {
  uint32_t opcode = PLAYER_DISCONNECT;
  uint32_t playerID = this->playerID;

  socket.send(&opcode, sizeof(opcode));
  socket.send(&playerID, sizeof(playerID));
}