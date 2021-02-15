#ifndef CLIENTMAPLOADER_H_
#define CLIENTMAPLOADER_H_

#include <string>
#include <vector>

#include "../../common/includes/YAML/YAMLMapReader.h"
#include "doortile.h"
#include "drawable.h"

typedef std::vector<std::vector<int>> WallIdMatrix;

class ClientMapLoader {
 public:
  ClientMapLoader(std::string& yamlFile);

  /**
   * @brief   Converts the id of a item in the yaml file, to the id that
   *          represents that same item in the protocol.
   */
  unsigned int convertYamlFileItemIdToProtocolItemSkinId(int yamlFileId);
  int* getWallIdMatrix();
  DoorTile* getDoorIdMatrix();

  /**
   * @return a vector with all the drawable items.
   */
  std::vector<Drawable*> getDrawableItemList();
  unsigned int dimx, dimy;

  /**
   * @return a vector with all the Coordinates where there is a door.
   */
  std::vector<Coordinate> getDoorCoordinates();

  std::vector<Coordinate> getFakeWallCoordinates();

 private:
  int uniqueid;
  YAMLMapReader yamlMapReader;
  WallIdMatrix wallIdMatrix;

  /**
   * @return a boolean that represents the existance of itemId as a key
   *        of coordinateMap.
   */
  bool idIsInCoordinateMap(
      std::map<int, std::vector<Coordinate>>& coordinateMap, int itemId);

  /**
   * @brief  Converts the id of a wall in the yaml file, to the id that
  represents that same wall in the protocol.
   */
  unsigned int convertYamlFileWallIdToProtocolWallSkinId(int yamlFileId);
};

#endif  // CLIENTMAPLOADER_H_
