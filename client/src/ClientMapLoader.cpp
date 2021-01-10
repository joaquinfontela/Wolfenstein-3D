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
    if (!this->idIsInWallCoordinateMap(wallTypeCoordinateMap, id)) continue;
    std::vector<Coordinate> coordinatesWhereWallWithCurrentIdIsIn =
        wallTypeCoordinateMap[id];
    for (Coordinate c : coordinatesWhereWallWithCurrentIdIsIn) {
      wallIdMatrix[c.getY()][c.getX()] =
          this->convertYamlFileWallIdToProtocolWallSkinId(id);
    }
  }
  return wallIdMatrix;
}

bool ClientMapLoader::idIsInWallCoordinateMap(
    std::map<int, std::vector<Coordinate>> wallTypeCoordinateMap, int itemId) {
  return (wallTypeCoordinateMap.find(itemId) != wallTypeCoordinateMap.end());
}

unsigned int ClientMapLoader::convertYamlFileWallIdToProtocolWallSkinId(
    int yamlFileId) {
  switch (yamlFileId) {
    case 301:
    case 351:
      return 301;
      break;

    case 302:
    case 352:
      return 302;
      break;

    case 303:
    case 353:
      return 303;
      break;

    case 304:
    case 354:
      return 304;
      break;

    default:
      throw std::runtime_error("Wall id recieved not valid.");
  }
}
