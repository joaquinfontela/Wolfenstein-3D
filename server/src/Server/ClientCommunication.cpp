#include "../../includes/Server/ClientCommunication.h"

#include <arpa/inet.h>

#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../../../common/includes/Socket/SocketException.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../../../common/includes/protocol.h"
#include "../../includes/Match/MatchList.h"

ClientCommunication::ClientCommunication(SocketCommunication peer, uint32_t id,
                                         MatchList& matches)
    : socket(std::move(peer)),
      playerID(id),
      running(true),
      matchList(matches) {}

bool ClientCommunication::isAlive() { return running; }

void ClientCommunication::run() {
  if (connectToLobby()) {
    this->handler->run();
    delete this->handler;
  }else{
    uint32_t opcode = CONNECTION_REFUSED;
    this->socket.send(&opcode, sizeof(opcode));
  }


  running = false;
}

unsigned int ClientCommunication::ID() { return this->playerID; }
bool ClientCommunication::connectToLobby() {
  // Armo un buffer para el opcode
  uint32_t opcode[1] = {0};

  try {
    this->socket.receive(opcode, sizeof(opcode));

    std::cout << "[SERVER] Client trying to join lobby" << std::endl;
    std::cout << "[SERVER] Received opcode: " << opcode[0] << std::endl;
    // Compruebo que el opcode sea el del protocolo para conexion.
    if (opcode[0] == JOIN_LOBBY) {
      uint32_t lobbyID[1] = {0};
      this->socket.receive(lobbyID, sizeof(lobbyID));


      std::cout << "[SERVER] Client joining lobby: " << int(lobbyID[0])
                << std::endl;

      this->handler = this->matchList.join(this, lobbyID[0]);

      if(this->handler != nullptr){
        uint32_t responseOpcode = CONNECTED_OK;
        this->socket.send(&responseOpcode, sizeof(responseOpcode));

        uint32_t playerID = this->playerID;
        int sent = this->socket.send(&playerID, sizeof(playerID));

        return true;
      }

      // TODO: Send CONNECTION_ERROR
      return false;

    }else if(opcode[0] == CREATE_LOBBY){
      uint32_t lobbyID[1] = {0};
      this->socket.receive(lobbyID, sizeof(lobbyID));


      std::cout << "[SERVER] Client creating lobby: " << int(lobbyID[0])
                << std::endl;

      this->handler = this->matchList.create(this, lobbyID[0]);

      if(this->handler != nullptr){
        uint32_t responseOpcode = CONNECTED_OK;
        this->socket.send(&responseOpcode, sizeof(responseOpcode));

        uint32_t playerID = this->playerID;
        int sent = this->socket.send(&playerID, sizeof(playerID));
        return true;
      }

      return false;

    }else{
      running = false;
      return false;
    }

  } catch (SocketException& e) {
    running = false;
    return false;
  }
}

SocketCommunication& ClientCommunication::getSock() { return this->socket; }
