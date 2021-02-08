#ifndef YAML_CONVERSOR_H
#define YAML_CONVERSOR_H

#include <QString>

#include "../../common/includes/YAML/YAMLMapReader.h"
#include "PathFactory.h"
#include "tile_item.h"

typedef std::vector<std::vector<std::vector<tile_item*>>> TileMatrix;

class YAMLConversor {
 private:
  std::string fileName;

  /**
   * @brief Return an empty matrix with mapDimensions dimensions.
   *
   * @param mapDimensions a vector representing two dimensions.
   * @return an empty matrix.
   */
  TileMatrix* createEmptyMatrix(std::vector<int> mapDimensions);

 public:
  YAMLConversor(std::string& fileName) : fileName(fileName) {}

  /**
   * @return an updated matrix with the data of the file given in the
   * constructor.
   */
  TileMatrix* updateTileMatrix();
};

#endif
