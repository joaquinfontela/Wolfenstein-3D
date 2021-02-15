#ifndef PLAYERMAP_H_
#define PLAYERMAP_H_

#include "player.h"
#include <map>

/**
 * @brief Dictionary with all the players, mapped by their id's.
 *
 */
class PlayerMap {
 private:
  Player* self;
 
  /**
  * @brief Deallocates all the resources.
  *
  */
  void garbageCollector();
 public:
  std::map<uint32_t, Player*> dict;
  PlayerMap(uint32_t selfId);
  ~PlayerMap();
 
  /**
  * @brief Verifies if the given player is included in the map.
  *
  * @param id Player id.
  * @returns true if the given player is in the map.
  */
  bool isContained(uint32_t id);
 
  /**
  * @brief Returns a pointer to the one's player. Must not be deleted.
  *
  * @returns player Reference to one's player.
  */
  Player* getSelf();
};

#endif  // PLAYERMAP_H_
