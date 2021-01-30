#include "../../../includes/Control/Notification/PlayerDied.h"

#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "../../../../common/includes/protocol.h"

PlayerDied::PlayerDied(int playerID) { this->playerID = playerID; }

void PlayerDied::send(SocketCommunication& socket) {
  uint32_t opcode = PLAYER_DIED;
  uint32_t playerID = this->playerID;

  socket.send(&opcode, sizeof(opcode));
  socket.send(&playerID, sizeof(playerID));
}
