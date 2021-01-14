#ifndef CLIENTMAPLOADER_H_
#define CLIENTMAPLOADER_H_

#include <string>
#include <vector>

#include "../../common/includes/YAML/YAMLMapReader.h"
#include "drawable.h"

typedef std::vector<std::vector<int>> WallIdMatrix;

class ClientMapLoader {
 public:
  ClientMapLoader(std::string& yamlFile, unsigned int dimx, unsigned int dimy);
  int* getWallIdMatrix();
  std::vector<Drawable*> getDrawableItemList();
  unsigned int dimx, dimy;

 private:
  int uniqueid;
  YAMLMapReader yamlMapReader;
  WallIdMatrix wallIdMatrix;
  bool idIsInCoordinateMap(std::map<int, std::vector<Coordinate>>& coordinateMap,
                           int itemId);
  unsigned int convertYamlFileWallIdToProtocolWallSkinId(int yamlFileId);
  unsigned int convertYamlFileItemIdToProtocolItemSkinId(int yamlFileId);
};

#endif  // CLIENTMAPLOADER_H_
