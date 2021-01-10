#include "./ClientMapLoader.h"

ClientMapLoader::ClientMapLoader(std::string& yamlFile, unsigned int dimx,
                                 unsigned int dimy)
    : yamlMapReader(yamlFile) {
  unsigned int x, y;
  for (y = 0; y < dimy; y++) {
    std::vector<int> wallIdRow;
    for (x = 0; x < dimx; x++) {
      wallIdRow.push_back(0);
    }
    this->wallIdMatrix.push_back(wallIdRow);
  }
}

WallIdMatrix ClientMapLoader::getWallIdMatrix() {
  int FROM_ID = yamlMapReader.getWallsIdLimits().at(0);
  int TO_ID = yamlMapReader.getWallsIdLimits().at(1);
  std::map<int, std::vector<Coordinate>> wallTypeCoordinateMap =
      yamlMapReader.getWallTypeCoordinateMap();
  int id;
  for (id = FROM_ID; id <= TO_ID; id++) {
    if (!this->idIsInCoordinateMap(wallTypeCoordinateMap, id)) continue;
    std::vector<Coordinate> coordinatesWhereWallWithCurrentIdIsIn =
        wallTypeCoordinateMap[id];
    for (Coordinate c : coordinatesWhereWallWithCurrentIdIsIn) {
      wallIdMatrix[c.getY()][c.getX()] =
          this->convertYamlFileWallIdToProtocolWallSkinId(id);
    }
  }
  return wallIdMatrix;
}

std::vector<Drawable*> ClientMapLoader::getDrawableItemList() {
  int FROM_ID = yamlMapReader.getItemsIdLimits().at(0);
  int TO_ID = yamlMapReader.getItemsIdLimits().at(1);
  std::map<int, std::vector<Coordinate>> itemTypeCoordinateMap =
      yamlMapReader.getItemTypeCoordinateMap();
  int id;
  std::vector<Drawable*> drawableItems;
  for (id = FROM_ID; id <= TO_ID; id++) {
    if (!this->idIsInCoordinateMap(itemTypeCoordinateMap, id)) continue;
    std::vector<Coordinate> coordinatesWhereItemWithCurrentIdIsIn =
        itemTypeCoordinateMap[id];
    for (Coordinate c : coordinatesWhereItemWithCurrentIdIsIn) {
      drawableItems.push_back(
          new Drawable(c.getX(), c.getY(),
                       this->convertYamlFileItemIdToProtocolItemSkinId(id)));
    }
  }
  return drawableItems;
}

bool ClientMapLoader::idIsInCoordinateMap(
    std::map<int, std::vector<Coordinate>> coordinateMap, int itemId) {
  return (coordinateMap.find(itemId) != coordinateMap.end());
}

unsigned int ClientMapLoader::convertYamlFileWallIdToProtocolWallSkinId(
    int yamlFileId) {
  switch (yamlFileId) {
    case 301:
    case 351:
      return 1;
      break;

    case 302:
    case 352:
      return 17;
      break;

    case 303:
    case 353:
      return 18;
      break;

    case 304:
    case 354:
      return 19;
      break;

    default:
      throw std::runtime_error("Wall id recieved not valid.");
  }
}

unsigned int ClientMapLoader::convertYamlFileItemIdToProtocolItemSkinId(
    int yamlFileId) {
  switch (yamlFileId) {
    case 101:
      return 33;
      break;

    case 102:
      return 32;
      break;

    case 103:
      return 34;
      break;

    case 104:
      return 35;
      break;

    case 105:
      return 36;
      break;

    case 106:
      return 37;
      break;

    case 107:
      return 30;
      break;

    case 108:
      return 38;
      break;

    case 109:
      return 31;
      break;

    default:
      throw std::runtime_error("Item id recieved not valid.");
  }
}