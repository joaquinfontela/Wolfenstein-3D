#include <iostream>
#include <algorithm>
#include <string>

#include "audio.h"
#include "commandexecuter.h"
#include "RaycastedAnimation.h"
#include "texturemanager.h"
#include "../../common/includes/Map/Map.h"
#include "../../common/includes/Socket/SocketWrapper.h"
#include "../../common/includes/PlayerData.h"
#include "../../common/includes/protocol.h"
#include "clientprotocol.h"

CommandExecuter::CommandExecuter(SocketCommunication& s, std::atomic<bool>& alive, std::vector<Drawable*>& sprites,
                                 std::map<uint32_t,Player*>& players, std::mutex& lock, int selfId,
                                 AudioManager& audiomanager, Map& matrix, ClientMapLoader& loader) :
                                 socket(s) , alive(alive) , sprites(sprites), players(players) , lock(lock) ,
                                 selfId(selfId) , audiomanager(audiomanager) , matrix(matrix) , loader(loader) {}

void CommandExecuter::loadNewTexture(double x, double y,
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

void CommandExecuter::eraseSprite(uint32_t itemId) {
  std::vector<Drawable*>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end(); ++it) {
    if ((*it)->hasThisUniqueId(itemId)) {
      delete (*it);
      this->sprites.erase(it);
      break;
    }
  }
}

void CommandExecuter::playExplosionSound() {
  this->audiomanager.playWithId(EXPLOSION_SOUND);
}

void CommandExecuter::removeSpriteWithId(uint32_t itemId) {
  this->lock.lock();
  std::cout << "[GAME] Removing sprite with id: " << itemId << std::endl;
  std::vector<Drawable*>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end(); ++it) {
    if ((*it)->hasThisUniqueId(itemId)) {
      int soundid = (*it)->id;
      delete (*it);
      this->sprites.erase(it);
      if (IS_HEALTH_UP(soundid)) {
        this->audiomanager.playWithId(HEALTH_PICKUP_SOUND);
      } else {
        this->audiomanager.playWithId(PICKUP_SOUND);
      }
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

void CommandExecuter::renderExplosionAnimation(uint32_t itemId) {
  double x = ERROR;
  double y = ERROR;
  std::vector<Drawable*>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end(); ++it) {
    if ((*it)->hasThisUniqueId(itemId)) {
      x = (*it)->x;
      y = (*it)->y;
      delete (*it);
      this->sprites.erase(it);
      break;
    }
  }
  if (x == ERROR || y == ERROR) std::cerr << "Error, no missile texture to explode found.\n";
  std::cout << "X: " << x << " Y: " << y << std::endl;
  this->sprites.push_back(new RaycastedAnimation(x, y, this, EXPLOSION, itemId,
                                                 EXPLOSION_FRAMES, FRAMES_PER_EXPLOSION_ANIMATION));
}

void CommandExecuter::renderDeathAnimation(uint32_t playerId) {
  Player* deadPlayer = this->players[playerId];
  int gunId = deadPlayer->weaponId;
  double dist = players.at(this->selfId)->calculateDist(players.at(playerId));
  int deathSpriteId = GET_DEATH_ANIMATION_SPRITE(gunId);
  // I don't need to get a new uniqueId for the sprite when I can use -1 * deadPlayer->playerId.
  // Not only it's a negative number, which means that no other texture could have the same id,
  // But that no other players can have the same id.
  this->playDyingSound(gunId, dist);
  this->sprites.push_back(new RaycastedAnimation(deadPlayer->x, deadPlayer->y, this,
                                                 deathSpriteId, -int(playerId),
                                                 DEATH_FRAMES, FRAMES_PER_DEATH_ANIMATION));
}

void CommandExecuter::playDyingSound(int gunId, double dist) {

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
      } else if (opcode == PLAYER_DIED) {
        uint32_t playerId;
        this->socket.receive(&playerId, sizeof(playerId));
        if (playerId != this->selfId)
          this->renderDeathAnimation(playerId);
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
        this->renderMovingSprite(x, y, uniqueId);
      } else if (opcode == MISSILE_EXPLOTION) {
        uint32_t uniqueId;
        this->socket.receive(&uniqueId, sizeof(uniqueId));
        this->audiomanager.playWithId(EXPLOSION_SOUND);
        this->renderExplosionAnimation(uniqueId);
      }
    } catch (SocketException& e) {
      break;
    }
  }
}
