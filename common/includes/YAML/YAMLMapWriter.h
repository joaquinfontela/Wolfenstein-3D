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

  // Returns a node with the data of the file given.
  YAML::Node getData();

  // Writes the X dimension of the map in the file.
  void addDimX();

  // Writes the Y dimension of the map in the file.
  void addDimY();

  // Writes the first id and the last id of each type of item (or object) of the
  // map in the file.
  void addItemTypesLimits();

  // Adds all the items of the TileMatrix to the map that will be written in
  // the file.
  void addAllItemsToMatrix();

  // Adds all the items of one coordinate of the TileMatrix, to the map that
  // will be written in the file.
  void processMatrixPosition(std::vector<tile_item*>& tiles, unsigned int x,
                             unsigned int y);

  // Adds the coordinate recieved as another value of the vector of coordinates
  // associated to the key objectId.
  void addCoordinateWhereObjectWithIdIsIn(int objectId, Coordinate& coordinate);

  // Writes the data accumulated in the YAMLNode into the file.
  void writeDataIntoFile();

 public:
  YAMLMapWriter(std::string& fileName);

  // Creates the map file with extension '.yaml' and name fileName with the data
  // in tileMatrix.
  void createYamlMapFile(TileMatrix& tileMatrix);
};