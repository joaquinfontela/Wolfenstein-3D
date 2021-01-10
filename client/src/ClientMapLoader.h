#include <string>
#include <vector>

#include "../../common/includes/YAML/YAMLMapReader.h"
//#include "./drawable.h"

typedef std::vector<std::vector<int>> WallIdMatrix;

class ClientMapLoader {
 public:
  ClientMapLoader(std::string& yamlFile, unsigned int dimx, unsigned int dimy);
  WallIdMatrix getWallIdMatrix();

 private:
  YAMLMapReader yamlMapReader;
  WallIdMatrix wallIdMatrix;
  bool idIsInWallCoordinateMap(
      std::map<int, std::vector<Coordinate>> wallTypeCoordinateMap, int itemId);
  unsigned int convertYamlFileWallIdToProtocolWallSkinId(int yamlFileId);
};