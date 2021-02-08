#ifndef PATH_FACTORY_H
#define PATH_FACTORY_H

#include <string>

class PathFactory {
 public:
  /**
   * @brief gets the path to the image of the tile tileId.
   *
   * @param tileId id representing a tile.
   * @return a path to a tile image.
   */
  std::string getTilePath(int tileId);
};

#endif