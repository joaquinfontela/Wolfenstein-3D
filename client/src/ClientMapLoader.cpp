#include "../includes/ClientMapLoader.h"

#include <iostream>

#include "../includes/clientprotocol.h"

ClientMapLoader::ClientMapLoader(std::string& yamlFile)
    : yamlMapReader(yamlFile), uniqueid(1) {
  std::vector<int> mapDimensions = yamlMapReader.getMapDimensions();
  this->dimx = mapDimensions.at(0);
  this->dimy = mapDimensions.at(1);
}

int* ClientMapLoader::getWallIdMatrix() {
  int* matrix = (int*)calloc(dimx * dimy, sizeof(int));

  int FROM_ID = yamlMapReader.getWallsIdLimits().at(0);
  int TO_ID = yamlMapReader.getWallsIdLimits().at(1);
  std::map<int, std::vector<Coordinate>> wallTypeCoordinateMap =
      yamlMapReader.getWallTypeCoordinateMap();

  int id;
  for (id = FROM_ID; id <= TO_ID; id++) {
    if (!this->idIsInCoordinateMap(wallTypeCoordinateMap, id)) continue;
    std::vector<Coordinate> coordinatesWhereWallWithCurrentIdIsIn =
        wallTypeCoordinateMap[id];
    for (Coordinate& c : coordinatesWhereWallWithCurrentIdIsIn) {
      matrix[(c.getY() - 1) * this->dimx + (c.getX() - 1)] =
          this->convertYamlFileWallIdToProtocolWallSkinId(id);
    }
  }

  int DOOR_FROM = yamlMapReader.getDoorsIdLimits().at(0);
  int DOOR_TO = yamlMapReader.getDoorsIdLimits().at(1);

  for (id = DOOR_FROM; id <= DOOR_TO; id++) {
    std::vector<Coordinate> pos =
        yamlMapReader.getTileCoordinatesWhereObjectIsIn(id);

    for (Coordinate& c : pos) {
      matrix[(c.getY() - 1) * this->dimx + (c.getX() - 1)] =
          this->convertYamlFileWallIdToProtocolWallSkinId(id);
    }
  }
  return matrix;
}

DoorTile* ClientMapLoader::getDoorIdMatrix() {
  DoorTile* doors = (DoorTile*)calloc(dimx * dimy, sizeof(DoorTile));
  std::vector<Coordinate> coords = this->getDoorCoordinates();
  for (int i = 0; i < sizeof(doors); i += sizeof(void*)) {
    doors[i].restart();
  }
  for (Coordinate& c : coords) {
    (doors + (c.getX() - 1) + (dimx * (c.getY() - 1)))->restart();
    (doors + (c.getX() - 1) + (dimx * (c.getY() - 1)))->isDoor = true;
    (doors + (c.getX() - 1) + (dimx * (c.getY() - 1)))->isFakeWall = false;
  }

  coords.clear();
  coords = this->getFakeWallCoordinates();
  for (Coordinate& c : coords) {
    (doors + (c.getX() - 1) + (dimx * (c.getY() - 1)))->restart();
    (doors + (c.getX() - 1) + (dimx * (c.getY() - 1)))->isDoor = true;
    (doors + (c.getX() - 1) + (dimx * (c.getY() - 1)))->isFakeWall = true;
  }
  return doors;
}

std::vector<Coordinate> ClientMapLoader::getFakeWallCoordinates(){

  int WALL_FROM = yamlMapReader.getWallsIdLimits().at(0) + 50;
  int WALL_TO = yamlMapReader.getWallsIdLimits().at(1);
  std::vector<Coordinate> coordinates;

  int id = 0;
  for (id = WALL_FROM; id <= WALL_TO; id++) {
    std::vector<Coordinate> pos =
        yamlMapReader.getTileCoordinatesWhereObjectIsIn(id);
    coordinates.insert(coordinates.end(), pos.begin(), pos.end());
  }

  return coordinates;

}

std::vector<Coordinate> ClientMapLoader::getDoorCoordinates() {
  int DOOR_FROM = yamlMapReader.getDoorsIdLimits().at(0);
  int DOOR_TO = yamlMapReader.getDoorsIdLimits().at(1);
  std::vector<Coordinate> coordinates;

  int id = 0;
  for (id = DOOR_FROM; id <= DOOR_TO; id++) {
    std::vector<Coordinate> pos =
        yamlMapReader.getTileCoordinatesWhereObjectIsIn(id);
    coordinates.insert(coordinates.end(), pos.begin(), pos.end());
  }

  return coordinates;
}

std::vector<Drawable*> ClientMapLoader::getDrawableItemList() {
  int FROM_ID = yamlMapReader.getWeaponsIdLimits().at(0);
  int TO_ID = yamlMapReader.getItemsIdLimits().at(1);
  std::map<int, std::vector<Coordinate>> itemTypeCoordinateMap =
      yamlMapReader.getPartialItemCoordinateMap(FROM_ID, TO_ID);
  int id;
  std::vector<Drawable*> drawableItems;

  for (id = FROM_ID; id <= TO_ID; id++) {
    if (!this->idIsInCoordinateMap(itemTypeCoordinateMap, id)) continue;
    std::vector<Coordinate> coordinatesWhereItemWithCurrentIdIsIn =
        itemTypeCoordinateMap[id];
    for (Coordinate& c : coordinatesWhereItemWithCurrentIdIsIn) {
      drawableItems.push_back(new Drawable(
          c.getY() - 0.5, c.getX() - 0.5,
          this->convertYamlFileItemIdToProtocolItemSkinId(id), uniqueid));
      uniqueid++;
    }
  }
  return drawableItems;
}

bool ClientMapLoader::idIsInCoordinateMap(
    std::map<int, std::vector<Coordinate>>& coordinateMap, int itemId) {
  return (coordinateMap.find(itemId) != coordinateMap.end());
}

unsigned int ClientMapLoader::convertYamlFileWallIdToProtocolWallSkinId(
    int yamlFileId) {
  switch (yamlFileId) {
    case 301:
    case 351:
      return BLUEWALL;
      break;

    case 302:
    case 352:
      return GREY_STONE_WALL;
      break;

    case 303:
    case 353:
      return COLORSTONE;
      break;

    case 304:
    case 354:
      return WOODEN_WALL;
      break;
    case 202:
      return DOOR;
      break;
    case 201:
      return LOCKED_DOOR;
      break;

    case 355:
    case 305:
      return MOSSY;
      break;

    case 356:
    case 306:
      return WALL2_SPRITE;
      break;

    case 357:
    case 307:
      return BRICKWALL;
      break;

    case 358:
    case 308:
      return PURPLEWALL;
      break;

    case 359:
    case 309:
      return EAGLE_WALL;
      break;

    case 360:
    case 310:
      return WALL5_SPRITE;
      break;

    case 361:
    case 311:
     return WALL_3;
      break;

    case 362:
    case 312:
      return GREY_STONE_WALL;
      break;

    default:
      throw std::runtime_error("Wall id recieved not valid.");
  }
}

unsigned int ClientMapLoader::convertYamlFileItemIdToProtocolItemSkinId(
    int yamlFileId) {
  switch (yamlFileId) {
    case 3:
      return MACHINEGUNITEM;
      break;

    case 4:
      return CHAINGUNITEM;
      break;

    case 5:
      return ROCKETLAUNCHERITEM;
      break;

    case 101:
      return AMMO;
      break;

    case 102:
      return BLOOD;
      break;

    case 103:
      return CHEST;
      break;

    case 104:
      return GOLDENCROSS;
      break;

    case 105:
      return GOLDENCROWN;
      break;

    case 106:
      return GOLDENCUP;
      break;

    case 107:
      return FOOD;
      break;

    case 108:
      return GOLDENKEY;
      break;

    case 109:
      return MEDKIT;
      break;

    case 110:
      return SMALLBARREL_SPRITE;
      break;

    case 111:
      return CAGESKELETON;
      break;

    case 112:
      return FLAG;
      break;

    case 113:
      return FLOORLAMP;
      break;

    case 114:
      return GREENBARREL;
      break;

    case 115:
      return GREENLIGHT_SPRITE;
      break;

    case 116:
      return GROUNDSKELETON;
      break;

    case 117:
      return HEAPOFBONES;
      break;

    case 118:
      return HUNGSKELETON;
      break;

    case 119:
      return PILLAR;
      break;

    case 120:
      return PLANT;
      break;

    case 121:
      return SPIKES;
      break;

    case 122:
      return TABLE;
      break;

    case 123:
      return WATER;
      break;

    case 404:
      return FLYINGMISSILE;
      break;

    default:
      throw std::runtime_error("Item id recieved not valid.");
  }
}
