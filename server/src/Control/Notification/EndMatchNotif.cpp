#include "../../../includes/Control/Notification/EndMatchNotif.h"
#include "../../../includes/Control/Notification/ScoreBoard.h"
#include "../../../../common/includes/protocol.h"

#include <iostream>

void EndMatchNotif::send(SocketCommunication& socket){
  uint32_t opcode = ENDING_MATCH;
  std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
  socket.send(&opcode, sizeof(opcode));
  this->scoreboard->send(socket);
}

EndMatchNotif::~EndMatchNotif() {
  delete this->scoreboard;
}
