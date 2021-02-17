#include "../../../includes/Control/Notification/ScoreBoard.h"
#include "../../../../common/includes/protocol.h"

void ScoreBoard::send(SocketWrapper& socket){
  socket.send(uint32_t(this->numberOfPlayers));
  for (int i = 0; i < this->numberOfPlayers; i++) {
    socket.send(this->players[i]);
    socket.send(this->scores[i]);
  }
}
