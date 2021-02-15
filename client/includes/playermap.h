#ifndef PLAYERMAP_H_
#define PLAYERMAP_H_

#include "player.h"
#include <map>

class PlayerMap {
 private:
  Player* self;
  void garbageCollector();
 public:
  std::map<uint32_t, Player*> dict;
  PlayerMap(uint32_t selfId);
  ~PlayerMap();
  bool isContained(uint32_t id);
  Player* getSelf();
};

#endif  // PLAYERMAP_H_
