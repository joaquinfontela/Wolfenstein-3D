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
      wrapper(socket),
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
    this->wrapper.send(opcode);
  }


  running = false;
}

unsigned int ClientCommunication::ID() { return this->playerID; }
bool ClientCommunication::connectToLobby() {
  // Armo un buffer para el opcode
  uint32_t opcode = -1;

  try {
    this->wrapper.receive(&opcode);

    std::cout << "[SERVER] Client trying to join lobby" << std::endl;
    std::cout << "[SERVER] Received opcode: " << opcode << std::endl;
    // Compruebo que el opcode sea el del protocolo para conexion.
    if (opcode == JOIN_LOBBY) {

      std::vector<int> availableMatches = this->matchList.getAvailableMatches();
      sendAvailableMatchData(availableMatches);
      if(availableMatches.size() == 0)
        return false;

      uint32_t lobbyID = -1;
      this->wrapper.receive(&lobbyID);

      this->handler = this->matchList.join(this, lobbyID);

      if(this->handler != nullptr){
        uint32_t responseOpcode = CONNECTED_OK;
        this->wrapper.send(responseOpcode);
        uint32_t mapID = this->matchList.getMapID(lobbyID);

        std::cout<<"[SERVER] Client joining match: "<<int(lobbyID)<<std::endl;

        uint32_t playerID = this->playerID;
        this->wrapper.send(playerID);
        this->wrapper.send(mapID);

        return true;
      }else
        return false;

    }else if(opcode == CREATE_LOBBY){
      uint32_t lobbyID = -1;
      this->wrapper.receive(&lobbyID);


      std::cout << "[SERVER] Client creating lobby: " << int(lobbyID)
                << std::endl;

      this->handler = this->matchList.create(this, lobbyID);

      if(this->handler != nullptr){
        uint32_t responseOpcode = CONNECTED_OK;
        this->wrapper.send(responseOpcode);

        uint32_t playerID = this->playerID;
        this->wrapper.send(playerID);
        return true;
      }else
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

void ClientCommunication::sendAvailableMatchData(std::vector<int>& matches){

  uint32_t amountOfMatches = matches.size();
  this->wrapper.send(amountOfMatches);

  for(auto& match : matches){
    uint32_t id = match;
    this->wrapper.send(id);
  }


}

SocketWrapper& ClientCommunication::getSock() { return this->wrapper; }
