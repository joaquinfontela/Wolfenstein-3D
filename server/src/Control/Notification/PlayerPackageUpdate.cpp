#include "../../../includes/Control/Notification/PlayerPackageUpdate.h"
#include "../../../../common/includes/Socket/SocketWrapper.h"

#include "../../../../common/includes/protocol.h"

PlayerPackageUpdate::PlayerPackageUpdate(int playerID, PlayerData data) {
  this->playerID = playerID;
  this->data = data;
}

void PlayerPackageUpdate::send(SocketCommunication& socket) {
  uint32_t opcode = PLAYER_UPDATE_PACKAGE;
  socket.send(&opcode, sizeof(opcode));

  SocketWrapper wrapper(socket);

  wrapper.send(this->data);

}
