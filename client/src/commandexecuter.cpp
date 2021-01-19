#include <iostream>
#include <algorithm>
#include <string>

#include "audio.h"
#include "commandexecuter.h"
#include "../../common/includes/Map/Map.h"
#include "../../common/includes/Socket/SocketWrapper.h"
#include "../../common/includes/PlayerData.h"
#include "../../common/includes/protocol.h"
#include "clientprotocol.h"

void CommandExecuter::loadNewTexture(uint32_t x, uint32_t y,
                                     uint32_t yamlId, uint32_t uniqueId) {
  unsigned int itemId = this->loader.convertYamlFileItemIdToProtocolItemSkinId(yamlId);
  this->sprites.push_back(new Drawable(y, x, itemId, uniqueId));
}

CommandExecuter::~CommandExecuter(){
  /*for (iterator_t it = this->players.begin(); it != this->players.end(); ++it){
    delete it->second;
  }*/
}

void CommandExecuter::playShootingSounds(int shooterId) {
  if (shooterId != this->selfId){
    std::cout << "[GAME] Playing enemy shooting sound. \n";
    int weaponId = players.at(shooterId)->weaponId;
    int soundId = GET_WEAPON_SOUND(weaponId);
    double dist = players.at(this->selfId)->calculateDist(players.at(shooterId));
    this->audiomanager.playOnVariableVolumeWithId(soundId, dist);
  }
}

void CommandExecuter::playDoorOpeningSound(int x, int y) {
  double dist = players.at(this->selfId)->calculateDist(x, y);
  if (dist < 0) dist = 1;
  this->audiomanager.playOnVariableVolumeWithId(DOOR_SOUND, dist*10);
}

void CommandExecuter::removeSpriteWithId(int itemId) {
  this->lock.lock();
  std::cout << "[GAME] Removing sprite with id: " << itemId << std::endl;
  std::vector<Drawable*>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end(); ++it) {
    if ((*it)->hasThisUniqueId(itemId)) {
      delete (*it);
      this->sprites.erase(it);
      this->audiomanager.playWithId(PICKUP_SOUND);
      break;
    }
  }
  this->lock.unlock();
}

void CommandExecuter::renderMovingSprite(double x, double y, uint32_t itemId) {
  std::vector<Drawable*>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end(); ++it) {
    if ((*it)->hasThisUniqueId(itemId)) {
      (*it)->x = x;
      (*it)->y = y;
      break;
    }
  }
}

void CommandExecuter::run() {
  SocketWrapper infogetter(this->socket);
  Audio eyeofthetiger("../audio/Wolfenstein-3D-Orchestral-Re-rec.mp3", IS_MUSIC, MUSIC_VOLUME);
  eyeofthetiger.volumeUp();
  eyeofthetiger.play();
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
        this->players.at(shooterId)->startShooting();
        this->playShootingSounds(shooterId);
      } else if (opcode == OPEN_DOOR) {
        uint32_t x, y;
        this->socket.receive(&x, sizeof(x));
        this->socket.receive(&y, sizeof(y));
        std::cout<<"[GAME] Switching door state at: " << x << ", " << y << std::endl;
        matrix.switchDoorState(x, y);
        this->playDoorOpeningSound(x, y);
      } else if (opcode == PLAYER_PICKUP_ITEM) {
        uint32_t itemId;
        this->socket.receive(&itemId, sizeof(itemId));
        std::cout<<"[GAME] Picking up item with id: " << itemId << ", there are: " << sprites.size() << " items left." << std::endl;
        this->removeSpriteWithId(itemId);
      } else if (opcode == PLAYER_DROP_ITEM) {
        uint32_t x, y, yamlId, uniqueId;
        this->socket.receive(&x, sizeof(x));
        this->socket.receive(&y, sizeof(y));
        this->socket.receive(&yamlId, sizeof(yamlId));
        this->socket.receive(&uniqueId, sizeof(uniqueId));
        std::cout<<"[GAME] Droping item with id: " << uniqueId << ", there are: " << sprites.size() << " items left." << std::endl;
        this->loadNewTexture(x, y, yamlId, uniqueId);
      } else if (opcode == ELEMENT_SWITCH_POSITION) {
        double x = infogetter.receiveDouble();
        double y = infogetter.receiveDouble();
        uint32_t uniqueId;
        this->socket.receive(&uniqueId, sizeof(uniqueId));
        this->renderMovingSprite(x, y, uniqueId);
      } else if (opcode == MISSILE_EXPLOTION) {
        uint32_t uniqueId;
        this->socket.receive(&uniqueId, sizeof(uniqueId));
      }
    } catch (SocketException& e) {
      break;
    }
  }
}
