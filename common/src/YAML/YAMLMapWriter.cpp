#include "../../includes/YAML/YAMLMapWriter.h"

#include <iostream>

YAMLMapWriter::YAMLMapWriter(std::string& fileName) {
  this->fileName = fileName;
}

YAML::Node YAMLMapWriter::getData() { return YAML::LoadFile(this->fileName); }

void YAMLMapWriter::addDimX() {
  unsigned int dimX = this->tileMatrix.at(0).size();
  this->data["dimx"] = dimX;
}

void YAMLMapWriter::addDimY() {
  unsigned int dimY = this->tileMatrix.size();
  this->data["dimy"] = dimY;
}

void YAMLMapWriter::addItemTypesLimits() {
  this->data["weapon id start"] = 1;
  this->data["weapon id end"] = 5;
  this->data["item id start"] = 101;
  this->data["item id end"] = 124;
  this->data["door id start"] = 201;
  this->data["door id end"] = 203;
  this->data["wall id start"] = 301;
  this->data["wall id end"] = 362;
}

void YAMLMapWriter::addAllItemsToMatrix() {
  unsigned int x;
  unsigned int y = 1;
  for (std::vector<std::vector<tile_item*>> row : tileMatrix) {
    x = 1;
    for (std::vector<tile_item*> column : row) {
      this->processMatrixPosition(column, x, y);
      x++;
    }
    y++;
  }
}

void YAMLMapWriter::processMatrixPosition(std::vector<tile_item*>& tiles,
                                          unsigned int x, unsigned int y) {
  for (tile_item* t : tiles) {
    int objectId = t->get_type();
    Coordinate coordinate(x, y);
    this->addCoordinateWhereObjectWithIdIsIn(objectId, coordinate);
  }
}

void YAMLMapWriter::addCoordinateWhereObjectWithIdIsIn(int objectId,
                                                       Coordinate& coordinate) {
  std::vector<std::vector<int>> coordinateVector;
  if (!this->data[objectId]) {
    coordinateVector.push_back(coordinate.getVector());
    this->data[objectId] = coordinateVector;
  } else {
    coordinateVector = this->data[objectId].as<std::vector<std::vector<int>>>();
    coordinateVector.push_back(coordinate.getVector());
    this->data[objectId] = coordinateVector;
  }
}

void YAMLMapWriter::writeDataIntoFile() {
  YAML::Emitter emitter;
  emitter << data;
  std::ofstream yamlFile(this->fileName);
  yamlFile << emitter.c_str();
}

void YAMLMapWriter::createYamlMapFile(TileMatrix& tileMatrix) {
  YAML::Node newNode;
  this->data = newNode;
  this->tileMatrix = tileMatrix;
  this->addDimX();
  this->addDimY();
  this->addItemTypesLimits();
  this->addAllItemsToMatrix();
  this->writeDataIntoFile();
}
