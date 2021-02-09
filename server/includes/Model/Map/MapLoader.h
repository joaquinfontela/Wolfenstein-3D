#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <map>
#include <vector>

#include "../../../../common/includes/Coordinate/Coordinate.h"
#include "../../../../common/includes/YAML/YAMLMapReader.h"
#include "../../../includes/Model/Door/DoorFactory.h"
#include "../../../includes/Model/Item/ItemFactory.h"
#include "../../../includes/Model/Item/Weapon/WeaponFactory.h"
#include "../../../includes/Model/Wall/WallFactory.h"
#include "../../../includes/Model/Wall/BlueWall.h"
#include "Map.h"

class Map;

class MapLoader {
 private:
  YAMLMapReader yamlReader;
  unsigned int weaponIdStart;
  unsigned int weaponIdEnd;
  unsigned int itemIdStart;
  unsigned int itemIdEnd;
  unsigned int doorIdStart;
  unsigned int doorIdEnd;
  unsigned int wallIdStart;
  unsigned int wallIdEnd;
  std::map<int, std::vector<Coordinate>> itemCoordinateMap;

  /*
   * @brief [SERVER-SIDE] Adds all the weapons in itemCoordinateMap to map.
   *
   * @param map a map of a game.
   *
   */
  void addWeaponsToMap(Map* map);

  /*
   * @brief [SERVER-SIDE] Adds all the items in itemCoordinateMap to map.
   *
   * @param map a map of a game.
   *
   */
  void addItemsToMap(Map* map);

  /*
   * @brief [SERVER-SIDE] Adds all the doors in itemCoordinateMap to map.
   *
   * @param map a map of a game.
   *
   */
  void addDoorsToMap(Map* map);

  /*
   * @brief [SERVER-SIDE] Adds all the walls in itemCoordinateMap to map.
   *
   * @param map a map of a game.
   *
   */
  void addWallsToMap(Map* map);

  /*
   * @return Returns true if itemId is a key in itemCoordinateMap, or
   * false otherwise.
   *
   * @param itemId
   */
  bool idIsInItemCoordinateMap(int itemId);

 public:
  MapLoader(std::string& yamlFile);

  /*
   * @return a dynamic pointer to a map loaded with the data in the yaml file
   * given in the constructor.
   */
  Map* loadMap();
};

#endif
