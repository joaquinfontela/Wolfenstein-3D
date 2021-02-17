#include "../../includes/Server/ConnectionHandler.h"

#include <thread>

#include "../../../common/includes/Socket/SocketException.h"
#include "../../../common/includes/Socket/SocketWrapper.h"
#include "../../../common/includes/protocol.h"
#include "../../includes/Control/Command/PlayerMove.h"
#include "../../includes/Control/Command/PlayerDisconnected.h"
#include "../../includes/Control/Command/PlayerWDown.h"
#include "../../includes/Control/Command/PlayerSDown.h"
#include "../../includes/Control/Command/PlayerADown.h"
#include "../../includes/Control/Command/PlayerDDown.h"
#include "../../includes/Control/Command/PlayerShoot.h"
#include "../../includes/Control/Command/PlayerWUp.h"
#include "../../includes/Control/Command/PlayerAUp.h"
#include "../../includes/Control/Command/PlayerSUp.h"
#include "../../includes/Control/Command/PlayerDUp.h"
#include "../../includes/Control/Command/PlayerInteractDoor.h"
#include "../../includes/Control/Command/PlayerSwitchWeapon.h"
#include "../../includes/Control/Command/StartGame.h"

ConnectionHandler::ConnectionHandler(SocketWrapper& sock,
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
      this->socket.receive(&opcode);

      switch (opcode){
        case KEY_A_DOWN:{

          PlayerADown* command = new PlayerADown(this->ID);
          this->commands.push(command);
          break;
        }
        case KEY_S_DOWN:{

          PlayerSDown* command = new PlayerSDown(this->ID);
          this->commands.push(command);
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

       case PLAYER_SHOOT_DOWN: {
         PlayerShoot* shoot = new PlayerShoot(this->ID, true);
         this->commands.push(shoot);
         break;
       }

       case PLAYER_SHOOT_UP: {
         PlayerShoot* shoot = new PlayerShoot(this->ID, false);
         this->commands.push(shoot);
         break;
       }

       case OPEN_DOOR: {
         PlayerInteractDoor* door = new PlayerInteractDoor(this->ID);
         this->commands.push(door);
         break;
       }

       case KEY_1_DOWN:{
         this->commands.push(new PlayerSwitchWeapon(this->ID, 0));
         break;
       }

      case KEY_2_DOWN:{
        this->commands.push(new PlayerSwitchWeapon(this->ID, 1));
        break;
      }

      case KEY_3_DOWN:{
        this->commands.push(new PlayerSwitchWeapon(this->ID, 2));
        break;
      }

      case KEY_4_DOWN:{
        this->commands.push(new PlayerSwitchWeapon(this->ID, 3));
        break;
      }

      case KEY_5_DOWN:{
        this->commands.push(new PlayerSwitchWeapon(this->ID, 4));
        break;
      }

      case START_MATCH:{
        this->commands.push(new StartGame(this->ID));
        break;
      }

      default:
          std::cout << "[ConnectionHandler] Unknown opcode received"<< std::endl;
      }
    } catch (SocketException& e) {
      PlayerDisconnected* playerDisc = new PlayerDisconnected(this->ID);
      this->commands.push(playerDisc);
      std::cout << "[ConnectionHandler] Player Connection Lost, ID: "
                << this->ID << std::endl;
      break;
    }
  }
}
