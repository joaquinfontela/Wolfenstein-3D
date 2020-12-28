#include "../../includes/Server/ConnectionHandler.h"

#include <thread>

#include "../../../common/includes/Socket/SocketException.h"
#include "../../../common/includes/protocol.h"
#include "../../includes/Control/Command/PlayerMove.h"
#include "../../includes/Control/Command/PlayerDisconnected.h"

ConnectionHandler::ConnectionHandler(SocketCommunication& sock,
                                     WaitingQueue<Command*>& com, int playerID)
    : socket(sock), commands(com), ID(playerID) {}

void ConnectionHandler::run() {
  std::thread receiverThread(&ConnectionHandler::receiveCommands, this);

  receiverThread.join();
}

void ConnectionHandler::receiveCommands() {
  while (true) {
    try {
      uint32_t opcode;
      this->socket.receive(&opcode, sizeof(opcode));

      switch (opcode) {
        case PLAYER_POS_UPDATE: {
          uint32_t x;
          this->socket.receive(&x, sizeof(x));
          uint32_t y;
          this->socket.receive(&y, sizeof(y));

          PlayerMove* command = new PlayerMove(this->ID, x, y);
          this->commands.push(command);
          std::cout << "[CONNECTION HANDLER] Player Move Opcode received"
                    << std::endl;
          break;
        }

        case PLAYER_DISCONNECT:{
          PlayerDisconnected* playerDisc = new PlayerDisconnected(this->ID);
          this->commands.push(playerDisc);
          break;
       }
        default:
          std::cout << "[ConnectionHandler] Unknow opcode received"
                    << std::endl;
      }
    } catch (SocketException& e) {
      // TODO -> Deberia tambien crear un comando de desconexion y pushearlo
      std::cout << "[ConnectionHandler] Player Connection Lost, ID: "
                << this->ID << std::endl;
      break;
    }
  }
}
