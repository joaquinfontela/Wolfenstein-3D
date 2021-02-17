#include "../../../includes/Control/Notification/MissileExplotion.h"
#include "../../../../common/includes/protocol.h"

MissileExplotion::MissileExplotion(int uniqueId) {
  this->uniqueId = uniqueId;
}

void MissileExplotion::send(SocketWrapper& socket) {
  uint32_t opcode = MISSILE_EXPLOTION;
  socket.send(opcode);

  uint32_t id = this->uniqueId;
  socket.send(id);

}
