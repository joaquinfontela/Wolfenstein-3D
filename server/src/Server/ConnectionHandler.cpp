#include "../../includes/Server/ConnectionHandler.h"

#include <thread>

#include "../../../common/includes/Socket/SocketException.h"
#include "../../../common/includes/protocol.h"
#include "../../includes/Control/Command/PlayerMove.h"
#include "../../includes/Control/Command/PlayerDisconnected.h"
#include "../../includes/Control/Command/PlayerWDown.h"
#include "../../includes/Control/Command/PlayerSDown.h"
#include "../../includes/Control/Command/PlayerADown.h"
#include "../../includes/Control/Command/PlayerDDown.h"

#include "../../includes/Control/Command/PlayerWUp.h"
#include "../../includes/Control/Command/PlayerAUp.h"
#include "../../includes/Control/Command/PlayerSUp.h"
#include "../../includes/Control/Command/PlayerDUp.h"

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

      switch (opcode){
        case KEY_A_DOWN:{

          PlayerADown* command = new PlayerADown(this->ID);
          this->commands.push(command);
          std::cout << "[CONNECTION HANDLER] Player Move Opcode received"
                    << std::endl;
          break;
        }
        case KEY_S_DOWN:{

          PlayerSDown* command = new PlayerSDown(this->ID);
          this->commands.push(command);
          std::cout << "[CONNECTION HANDLER] Player Move Opcode received"
                    << std::endl;
          break;
        }

        case KEY_D_DOWN:{

          PlayerDDown* command = new PlayerDDown(this->ID);
          this->commands.push(command);
          break;
        }
        case KEY_W_DOWN:{

          PlayerWDown* command = new PlayerWDown(this->ID);
          this->commands.push(command);
          break;
        }

        case KEY_A_UP:{

          PlayerAUp* command = new PlayerAUp(this->ID);
          this->commands.push(command);
          break;
        }

        case KEY_S_UP:{

          PlayerSUp* command = new PlayerSUp(this->ID);
          this->commands.push(command);
          break;
        }

        case KEY_D_UP:{

          PlayerDUp* command = new PlayerDUp(this->ID);
          this->commands.push(command);

          break;
        }

        case KEY_W_UP:{

          PlayerWUp* command = new PlayerWUp(this->ID);
          this->commands.push(command);

          break;
        }

        case PLAYER_DISCONNECT:{
          PlayerDisconnected* playerDisc = new PlayerDisconnected(this->ID);
          this->commands.push(playerDisc);
          break;
       }

       case PLAYER_SHOOT: {
         PlayerShoot* shoot = new PlayerShoot(this->ID);
         this->commands.push(shoot);
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
