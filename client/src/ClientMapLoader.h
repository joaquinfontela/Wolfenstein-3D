#ifndef CLIENTMAP_LOADER_H_
#define CLIENTMAP_LOADER_H_

#include <string>
#include <vector>

#include "../../common/includes/YAML/YAMLMapReader.h"
#include "drawable.h"

typedef std::vector<std::vector<int>> WallIdMatrix;

class ClientMapLoader {
 public:
  ClientMapLoader(std::string& yamlFile, unsigned int dimx, unsigned int dimy);
  WallIdMatrix getWallIdMatrix();
  std::vector<Drawable*> getDrawableItemList();

 private:
  YAMLMapReader yamlMapReader;
  WallIdMatrix wallIdMatrix;
  bool idIsInCoordinateMap(std::map<int, std::vector<Coordinate>>& coordinateMap,
                           int itemId);
  unsigned int convertYamlFileWallIdToProtocolWallSkinId(int yamlFileId);
  unsigned int convertYamlFileItemIdToProtocolItemSkinId(int yamlFileId);
};

#endif  // CLIENTMAP_LOADER_H_
