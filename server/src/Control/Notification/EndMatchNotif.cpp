#include "../../../includes/Control/Notification/EndMatchNotif.h"

#include <iostream>

#include "../../../../common/includes/protocol.h"
#include "../../../includes/Control/Notification/ScoreBoard.h"

void EndMatchNotif::send(SocketWrapper& socket) {
  uint32_t opcode = ENDING_MATCH;

  socket.send(opcode);
  this->scoreboard->send(socket);
  this->killScoreboard->send(socket);
  this->shotsScoreboard->send(socket);
}

EndMatchNotif::~EndMatchNotif() {
  delete this->scoreboard;
  delete this->killScoreboard;
  delete this->shotsScoreboard;
}
