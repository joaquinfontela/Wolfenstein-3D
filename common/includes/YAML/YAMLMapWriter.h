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

  /*
   * @return a node with the data of the file given.
   */
  YAML::Node getData();

  // @brief Writes the X dimension of the map in the file.
  void addDimX();

  // @brief Writes the Y dimension of the map in the file.
  void addDimY();

  // @brief Writes the first id and the last id of each type of item (or object)
  // of the map in the file.
  void addItemTypesLimits();

  // @brief Adds all the items of the TileMatrix to the map that will be written
  // in the file.
  void addAllItemsToMatrix();

  // @brief Adds all the items of one coordinate of the TileMatrix, to the map
  // that will be written in the file.
  // @param tiles a vector of tiles (a concrete position of a TileMatrix)
  // @param x the x component of the coordinate.
  // @param y the y component of the coordinate.
  void processMatrixPosition(std::vector<tile_item*>& tiles, unsigned int x,
                             unsigned int y);

  // @brief Adds the coordinate recieved as another value of the vector of
  // coordinates associated to the key objectId.
  // @param objectId differentiates a type of an object from the other types.
  // @param coordinate an object that represents a coordinate.
  void addCoordinateWhereObjectWithIdIsIn(int objectId, Coordinate& coordinate);

  // @brief Writes the data accumulated in the YAMLNode into the file.
  void writeDataIntoFile();

 public:
  YAMLMapWriter(std::string& fileName);

  // @brief Creates the map file with extension '.yaml' and name fileName with
  // the data in tileMatrix.
  // @param tileMatrix a reference to a matrix of vectors of tile items.
  void createYamlMapFile(TileMatrix& tileMatrix);
};