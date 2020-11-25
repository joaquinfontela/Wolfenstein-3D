#include "../../includes/Server/ClientCommunication.h"

#include <arpa/inet.h>

#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../../../common/includes/Socket/SocketException.h"
#include "../../../common/includes/Thread/Thread.h"
#include "../../../common/includes/protocol.h"
#include "../../includes/Match/MatchList.h"

ClientCommunication::ClientCommunication(SocketCommunication peer,
                                         unsigned int id, MatchList& matches)
    : socket(std::move(peer)),
      playerID(id),
      running(true),
      matchList(matches) {}

bool ClientCommunication::isAlive() { return running; }

void ClientCommunication::run() {
  connectToLobby();
  running = false;
}

unsigned int ClientCommunication::ID() { return this->playerID; }
void ClientCommunication::connectToLobby() {
  // Armo un buffer para el opcode
  uint32_t opcode[1] = {0};

  try {
    this->socket.receive(opcode, sizeof(opcode));

    std::cout << "[SERVER] Client trying to join lobby" << std::endl;
    std::cout << "[SERVER] Received opcode: " << opcode[0] << std::endl;
    // Compruebo que el opcode sea el del protocolo para conexion.
    if (opcode[0] == CONNECT_TO_LOBBY) {
      uint32_t lobbyID[1] = {0};
      this->socket.receive(lobbyID, sizeof(lobbyID));

      std::cout << "[SERVER] Client joining lobby: " << int(lobbyID[0])
                << std::endl;

      this->matchList.joinOrCreate(this, lobbyID[0]);

      uint32_t responseOpcode = CONNECTED_OK;
      this->socket.send(&responseOpcode, sizeof(responseOpcode));

      uint32_t playerID = this->playerID;
      this->socket.send(&playerID, sizeof(playerID));

      // TODO -> Crear notificacion de que se conecto un jugador y pasar su ID.
    } else {
      running = false;
    }

  } catch (SocketException& e) {
    running = false;
  }
}
