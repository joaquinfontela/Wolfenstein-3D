#include "../../../includes/Control/Notification/ShotsFired.h"

#include "../../../../common/includes/protocol.h"

ShotsFired::ShotsFired(int playerID) : playerID(playerID){}

void ShotsFired::send(SocketWrapper& socket){

  uint32_t opcode = SHOTS_FIRED;

  socket.send(opcode);

  uint32_t playerID = this->playerID;

  socket.send(playerID);

}
