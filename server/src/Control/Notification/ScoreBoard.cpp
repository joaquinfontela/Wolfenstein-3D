#include "../../../includes/Control/Notification/ScoreBoard.h"
#include "../../../../common/includes/protocol.h"

void ScoreBoard::send(SocketCommunication& socket){
  socket.send((uint32_t*)(&this->numberOfPlayers), sizeof(uint32_t));
  for (int i = 0; i < this->numberOfPlayers; i++) {
    socket.send(&this->players[i], sizeof(uint32_t));
    socket.send(&this->scores[i], sizeof(uint32_t));
  }
}
