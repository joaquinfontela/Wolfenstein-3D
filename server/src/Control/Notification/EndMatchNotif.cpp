#include "../../../includes/Control/Notification/EndMatchNotif.h"
#include "../../../includes/Control/Notification/ScoreBoard.h"
#include "../../../../common/includes/protocol.h"

#include <iostream>

void EndMatchNotif::send(SocketCommunication& socket){
  uint32_t opcode = ENDING_MATCH;

  socket.send(&opcode, sizeof(opcode));
  this->scoreboard->send(socket);
  //this->killScoreboard->send(socket);
}

EndMatchNotif::~EndMatchNotif() {
  std::cout<<"Destructor called."<<std::endl;
  delete this->scoreboard;
  delete this->killScoreboard;
}
