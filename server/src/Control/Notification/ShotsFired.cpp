#include "../../../includes/Control/Notification/ShotsFired.h"

#include "../../../../common/includes/protocol.h"

ShotsFired::ShotsFired(int playerID) : playerID(playerID){}

void ShotsFired::send(SocketCommunication& socket){

  uint32_t opcode = SHOTS_FIRED;

  socket.send(&opcode, sizeof(opcode));

  uint32_t playerID = this->playerID;

  socket.send(&playerID, sizeof(playerID));

}
