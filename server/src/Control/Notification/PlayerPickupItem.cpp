#include "../../../includes/Control/Notification/PlayerPickUpItem.h"
#include "../../../../common/includes/protocol.h"

PlayerPickupItem::PlayerPickupItem(int uniqueId) {
  this->uniqueId = uniqueId;
}

void PlayerPickupItem::send(SocketCommunication& socket) {
  uint32_t opcode = PLAYER_PICKUP_ITEM;
  socket.send(&opcode, sizeof(opcode));

  uint32_t id = this->uniqueId;
  socket.send(&id, sizeof(id));

}
