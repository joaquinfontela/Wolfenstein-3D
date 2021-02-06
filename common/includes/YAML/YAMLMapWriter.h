#include <yaml-cpp/yaml.h>

#include <fstream>
#include <string>

#include "../../../qt/editor/tile_item.h"
#include "../Coordinate/Coordinate.h"

typedef std::vector<std::vector<std::vector<tile_item*>>> TileMatrix;

class YAMLMapWriter {
 private:
  std::string fileName;
  YAML::Node data;
  TileMatrix tileMatrix;
  YAML::Node getData();
  void addDimX();
  void addDimY();
  void addItemTypesLimits();
  void addAllItemsToMatrix();
  void processMatrixPosition(std::vector<tile_item*>& tiles, unsigned int x,
                             unsigned int y);
  void addCoordinateWhereObjectWithIdIsIn(int objectId, Coordinate& coordinate);
  void writeDataIntoFile();

 public:
  YAMLMapWriter(std::string& fileName);
  void createYamlMapFile(TileMatrix& tileMatrix);
};