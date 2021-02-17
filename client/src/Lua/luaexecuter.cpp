#include "luaexecuter.h"

#include "../../../common/includes/Map/Map.h"
#include "../../common/includes/PlayerData.h"
#include "../../common/includes/Socket/SocketWrapper.h"
#include "../../common/includes/protocol.h"
#include "../includes/clientprotocol.h"
#include "../includes/playermap.h"

namespace Lua {

void CommandExecuter::loadNewTexture(double x, double y, uint32_t yamlId,
                                     uint32_t uniqueId) {
  unsigned int itemId =
      this->loader.convertYamlFileItemIdToProtocolItemSkinId(yamlId);
  this->sprites.push_back(new Drawable(y, x, itemId, uniqueId));
}

void CommandExecuter::removeSpriteWithId(uint32_t itemId) {
  std::cout << "[GAME] Removing sprite with id: " << itemId << std::endl;
  gameState.clearVisibleItems();
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

void CommandExecuter::disconnectPlayer() {
  uint32_t id;
  this->socket.receive(&id);
  if (id == this->selfId) return;
  this->lock.lock();
  gameState.clearVisibleItems();
  Player* toKill = players.dict[id];
  players.dict.erase(id);
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
}

void CommandExecuter::openDoor() {
  uint32_t x, y;
  this->socket.receive(&x);
  this->socket.receive(&y);
  std::cout << "[GAME] Switching door state at: " << x << ", " << y
            << std::endl;
  matrix.switchDoorState(x, y);
}

void CommandExecuter::pickUpItem() {
  uint32_t itemId;
  this->socket.receive(&itemId);
  std::cout << "[GAME] Picking up item with id: " << itemId
            << ", there are: " << sprites.size() << " items left."
            << std::endl;
  this->removeSpriteWithId(itemId);
}

void CommandExecuter::dropItem(SocketWrapper& infogetter) {
  uint32_t yamlId, uniqueId;
  double x, y;
  this->socket.receive(&x);
  this->socket.receive(&y);
  this->socket.receive(&yamlId);
  this->socket.receive(&uniqueId);
  std::cout << "[GAME] Droping item with id: " << uniqueId
            << ", there are: " << sprites.size() << " items left."
            << std::endl;
  this->loadNewTexture(x, y, yamlId, uniqueId);
}

void CommandExecuter::switchElementPosition(SocketWrapper& infogetter) {
  uint32_t uniqueId;
  this->socket.receive(&uniqueId);
  double x, y;
  this->socket.receive(&x);
  this->socket.receive(&y);
}

void CommandExecuter::updateOrCreatePlayer(SocketWrapper& infogetter) {
  PlayerData playerinfo;
  memset(&playerinfo, 0, sizeof(PlayerData));
  this->socket.receivePlayerData(playerinfo);
  uint32_t id = playerinfo.playerID;
  if (players.dict.find(id) != players.dict.end()) {
    players.dict[id]->update(playerinfo);
  } else {
    Player* placeholder = new Player(playerinfo);
    if (!placeholder) {
      LOG(COULD_NOT_CREATE_PLAYER);
      return;
    }
    players.dict[id] = placeholder;
    this->sprites.push_back(placeholder);
  }
}

void CommandExecuter::run() {
  SocketWrapper infogetter(this->socket);
  while (alive) {
    try {
      uint32_t opcode;
      this->socket.receive(&opcode);
      if (opcode == PLAYER_UPDATE_PACKAGE) {  // Cambiar por switch
        this->updateOrCreatePlayer(infogetter);
      } else if (opcode == PLAYER_DISCONNECT) {
        this->disconnectPlayer();
      } else if (opcode == SHOTS_FIRED) {
        uint32_t shooterId;
        this->socket.receive(&shooterId);
      } else if (opcode == OPEN_DOOR) {
        this->openDoor();
      } else if (opcode == PLAYER_PICKUP_ITEM) {
        this->pickUpItem();
      } else if (opcode == PLAYER_DIED) {
        uint32_t playerId;
        this->socket.receive(&playerId);
      } else if (opcode == PLAYER_DROP_ITEM) {
        this->dropItem(infogetter);
      } else if (opcode == ELEMENT_SWITCH_POSITION) {
        this->switchElementPosition(infogetter);
      } else if (opcode == MISSILE_EXPLOTION) {
        uint32_t uniqueId;
        this->socket.receive(&uniqueId);
      }
    } catch (SocketException& e) {
    } catch (std::exception& e) {
      LOG(e.what());
      break;
    }
  }
}

}  // namespace Lua
