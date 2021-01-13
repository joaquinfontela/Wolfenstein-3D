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

CommandExecuter::~CommandExecuter(){
  /*for (iterator_t it = this->players.begin(); it != this->players.end(); ++it){
    delete it->second;
  }*/
}

void CommandExecuter::playShootingSounds(int shooterId) {
  int weaponId = players.at(shooterId)->weaponId;
  int soundId = GET_WEAPON_SOUND(weaponId);
  if (shooterId == this->selfId){
    this->audiomanager.playOnMaxVolumeWithId(soundId);
    // Hacer que pueda variar en función del arma.
  } else {
    double dist = players.at(this->selfId)->calculateDist(players.at(shooterId));
    this->audiomanager.playOnVariableVolumeWithId(soundId, dist);
  }
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
          std::cout << "Agrego player con id: " << id << std::endl;
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
        std::cout << "Killing player with id: " << id << std::endl;
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
        std::cout<<"Opening door at: "<<x<<", "<<y<<std::endl;
        matrix.openDoor(x, y);
      }
    } catch (SocketException& e) {
      break;
    }
  }
}
