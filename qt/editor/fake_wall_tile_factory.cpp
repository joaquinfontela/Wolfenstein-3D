#include "fake_wall_tile_factory.h"
#include "PathFactory.h"

fake_wall_tile_factory::fake_wall_tile_factory(){}

tile_item *fake_wall_tile_factory::get_tile(std::vector<int> &coordinates)
{
    int col = coordinates[0];
    int row = coordinates[1];
    int tipo;
    if (col == 1 && row == 4) {
      tipo = 351;
    } else if (col == 1 && row == 3) {
      tipo = 353;
    } else if (col == 2 && row == 5) {
      tipo = 359;
    } else if (col == 1 && row == 2) {
      tipo = 352;
    } else if (col == 1 && row == 5) {
      tipo = 360;
    } else if (col == 1 && row == 1) {
      tipo = 355;
    } else if (col == 2 && row == 6) {
      tipo = 361;
    } else if (col == 2 && row == 4) {
      tipo = 358;
    } else if (col == 2 && row == 3) {
      tipo = 357;
    } else if (col == 1 && row == 6) {
      tipo = 356;
    } else if (col == 2 && row == 2) {
      tipo = 362;
    } else {
      tipo = 354;
    }
    std::string path(PathFactory().getTilePath(tipo).c_str());
    tile_item* tile = new class tile_item(path, tipo, false);
    return tile;
}
