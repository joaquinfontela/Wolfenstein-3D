#ifndef YAML_MAP_READER_H
#define YAML_MAP_READER_H

#include <yaml-cpp/yaml.h>

#include <iostream>
#include <map>
#include <string>

#include "../Coordinate/Coordinate.h"

class YAMLMapReader {
 private:
  std::string fileName;
  YAML::Node data;

  //   Returns a node with the data of the file given
  YAML::Node getData();

  // Recieves a vector of vectors of size two (each of them representing a
  // coordinate), and returns a vector of objects of the class Coordinate.
  std::vector<Coordinate> getCoordinateVectorFromVectorOfVectorsOfSizeTwo(
      std::vector<std::vector<int>>& coordinatesData);

 public:
  //   Returns a map where the keys are the ids of the items (doors, walls,
  //   etc.) from FROM_ID to TO_ID, and the values are vectors of Coordinates
  //   where the objects with the id of the key are.
  std::map<int, std::vector<Coordinate>> getPartialItemCoordinateMap(
      int FROM_ID, int TO_ID);

  YAMLMapReader(std::string& fileName);

  //   Returns a vector of Coordinates where the objects with the id objectId
  //   are.
  std::vector<Coordinate> getTileCoordinatesWhereObjectIsIn(int objectId);

  //   Returns a vector of Coordinates where the respawn locations are.
  std::vector<Coordinate> getRespawnLocations();

  //   Returns a map where the keys are the ids of ALL the items (doors, walls,
  //   etc.) and the values are vectors of Coordinates where the objects with
  //   the id of the key are.
  std::map<int, std::vector<Coordinate>> getItemCoordinateMap();

  //   Returns a map where the keys are the ids of the walls (doors, walls,
  //   etc.) and the values are vectors of Coordinates where the objects with
  //   the id of the key are.
  std::map<int, std::vector<Coordinate>> getWallTypeCoordinateMap();

  //   Returns a map where the keys are the ids of the items
  //   and the values are vectors of Coordinates where the objects with
  //   the id of the key are.
  std::map<int, std::vector<Coordinate>> getItemTypeCoordinateMap();

  //   Returns a vector where the first element is the X dimension of the map,
  //   and the second, the Y dimension.
  std::vector<int> getMapDimensions();

  //   Returns a vector where the first element is the first id of a weapon,
  //   and the second, the last one.
  std::vector<int> getWeaponsIdLimits();

  //   Returns a vector where the first element is the first id of an item,
  //   and the second, the last one.
  std::vector<int> getItemsIdLimits();

  //   Returns a vector where the first element is the first id of a door,
  //   and the second, the last one.
  std::vector<int> getDoorsIdLimits();

  //   Returns a vector where the first element is the first id of a wall,
  //   and the second, the last one.
  std::vector<int> getWallsIdLimits();
};

#endif
