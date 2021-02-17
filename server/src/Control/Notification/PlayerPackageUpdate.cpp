#include "../../../includes/Control/Notification/PlayerPackageUpdate.h"
#include "../../../../common/includes/Socket/SocketWrapper.h"

#include "../../../../common/includes/protocol.h"

PlayerPackageUpdate::PlayerPackageUpdate(int playerID, PlayerData data) {
  this->playerID = playerID;
  this->data = data;
}

void PlayerPackageUpdate::send(SocketWrapper& socket) {
  uint32_t opcode = PLAYER_UPDATE_PACKAGE;
  socket.send(opcode);

  socket.send(uint32_t(this->playerID));

  socket.send(this->data);

}
