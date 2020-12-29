#include "commandexecuter.h"
#include "../../common/includes/Socket/SocketWrapper.h"
#include "../../common/includes/PlayerData.h"
#include "../../common/includes/protocol.h"

CommandExecuter::~CommandExecuter(){
  for (iterator_t it = this->players.begin(); it != this->players.end(); ++it){
    delete it->second;
  }
}

void CommandExecuter::run(){
  SocketWrapper infogetter(this->socket);
  while (alive) {
    try {
      uint32_t opcode;
      socket.receive(&opcode, sizeof(opcode));
      if (opcode == PLAYER_UPDATE_PACKAGE) {
        PlayerData playerinfo;
        infogetter.receivePlayerData(playerinfo);
        uint32_t id = playerinfo.playerID;
        if (players.find(id) != players.end()) {
          players[id]->update(playerinfo);
        } else {
          Player* placeholder = new Player(playerinfo);
          players[id] = placeholder;
          sprites.push_back(placeholder);
        }
      }
    } catch (SocketException& e) {
      break;
    }
  }
}
