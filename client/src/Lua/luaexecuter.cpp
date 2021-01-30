#include "luaexecuter.h"
#include "../../../common/includes/Map/Map.h"
#include "../../common/includes/Socket/SocketWrapper.h"
#include "../../common/includes/PlayerData.h"
#include "../../common/includes/protocol.h"
#include "../clientprotocol.h"

namespace Lua {

  void CommandExecuter::loadNewTexture(double x, double y,
                                       uint32_t yamlId, uint32_t uniqueId) {
    unsigned int itemId = this->loader.convertYamlFileItemIdToProtocolItemSkinId(yamlId);
    this->sprites.push_back(new Drawable(y, x, itemId, uniqueId));
  }

  void CommandExecuter::removeSpriteWithId(uint32_t itemId) {
    std::cout << "[GAME] Removing sprite with id: " << itemId << std::endl;
    this->lock.lock();
    std::vector<Drawable*>::iterator it = this->sprites.begin();
    for (; it != this->sprites.end(); ++it) {
      if ((*it)->hasThisUniqueId(itemId)) {
        int soundid = (*it)->id;
        delete (*it);
        this->sprites.erase(it);
        break;
      }
    }
    this->lock.unlock();
  }

  void CommandExecuter::run() {
    SocketWrapper infogetter(this->socket);
    while (alive) {
      try {
        uint32_t opcode;
        socket.receive(&opcode, sizeof(opcode));
        if (opcode == PLAYER_UPDATE_PACKAGE) { // Cambiar por switch
          PlayerData playerinfo;
          memset(&playerinfo, 0, sizeof(PlayerData));
          infogetter.receivePlayerData(playerinfo);
          uint32_t id = playerinfo.playerID;

          if (players.find(id) != players.end()) {
            players[id]->update(playerinfo);
          } else {
            std::cout << "[GAME] Adding player with id: " << id << std::endl;
            Player* placeholder = new Player(playerinfo);
            players[id] = placeholder;
            sprites.push_back(placeholder);
          }
        } else if (opcode == PLAYER_DISCONNECT) {
          uint32_t id;
          this->socket.receive(&id, sizeof(id));
          if (id == this->selfId) continue;
          this->lock.lock();
          Player* toKill = players[id];
          players.erase(id);
          std::vector<Drawable*>::iterator it = this->sprites.begin();
          for (; it != this->sprites.end(); ++it) {
            if (*it == toKill) {
              this->sprites.erase(it);
              break;
            }
          }
          std::cout << "[GAME] Killing player with id: " << id << std::endl;
          delete toKill;
          this->lock.unlock();
        } else if (opcode == SHOTS_FIRED) {
          uint32_t shooterId;
          this->socket.receive(&shooterId, sizeof(shooterId));
        } else if (opcode == OPEN_DOOR) {
          uint32_t x, y;
          this->socket.receive(&x, sizeof(x));
          this->socket.receive(&y, sizeof(y));
          std::cout<<"[GAME] Switching door state at: " << x << ", " << y << std::endl;
          matrix.switchDoorState(x, y);
        } else if (opcode == PLAYER_PICKUP_ITEM) {
          uint32_t itemId;
          this->socket.receive(&itemId, sizeof(itemId));
          std::cout<<"[GAME] Picking up item with id: " << itemId << ", there are: " << sprites.size() << " items left." << std::endl;
          this->removeSpriteWithId(itemId);
        } else if (opcode == PLAYER_DIED) {
          uint32_t playerId;
          this->socket.receive(&playerId, sizeof(playerId));
        } else if (opcode == PLAYER_DROP_ITEM) {
          uint32_t  yamlId, uniqueId;
          double x, y;
          x = infogetter.receiveDouble();
          y = infogetter.receiveDouble();
          this->socket.receive(&yamlId, sizeof(yamlId));
          this->socket.receive(&uniqueId, sizeof(uniqueId));
          std::cout<<"[GAME] Droping item with id: " << uniqueId << ", there are: " << sprites.size() << " items left." << std::endl;
          this->loadNewTexture(x, y, yamlId, uniqueId);
        } else if (opcode == ELEMENT_SWITCH_POSITION) {
          uint32_t uniqueId;
          this->socket.receive(&uniqueId, sizeof(uniqueId));
          double x = infogetter.receiveDouble();
          double y = infogetter.receiveDouble();
        } else if (opcode == MISSILE_EXPLOTION) {
          uint32_t uniqueId;
          this->socket.receive(&uniqueId, sizeof(uniqueId));
        }
      } catch (SocketException& e) {
      } catch (std::exception& e) {
        LOG(e.what());
        break;
      }
    }
  }

}
