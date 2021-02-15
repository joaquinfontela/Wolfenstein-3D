#include "../includes/playermap.h"
#include "../includes/clientprotocol.h"
#include "../includes/player.h"

#include <algorithm>

PlayerMap::PlayerMap(uint32_t selfId) :
                     self(new Player(3.0, 3.0, -1.0, 0.0, 0.0, 0.66, 0)) {
  if (this->self == nullptr) {
    throw std::runtime_error(COULD_NOT_CREATE_PLAYER);
  }
  this->dict[selfId] = this->self;
}

Player* PlayerMap::getSelf() {
  return this->self;
}

PlayerMap::~PlayerMap() {
  this->garbageCollector();
}

void PlayerMap::garbageCollector() {
  delete this->self;
}

bool PlayerMap::isContained(uint32_t id) {
  return (this->dict.find(id) != this->dict.end());
}
