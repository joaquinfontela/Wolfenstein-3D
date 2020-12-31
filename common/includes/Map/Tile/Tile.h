#include <vector>

//#include "../../../../server/includes/Model/Item/ItemDrop/ItemDrop.h"

class Tile {
 private:
  int x;
  int y;
  std::vector<int> dropsIds;

 public:
  Tile(int x, int y);
  void addDrop(int id);
  std::vector<int> getDropIds();
};