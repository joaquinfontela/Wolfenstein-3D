#include "fake_wall_tile_factory.h"

fake_wall_tile_factory::fake_wall_tile_factory(){}

tile_item *fake_wall_tile_factory::get_tile(std::vector<int> &coordinates)
{
    int col = coordinates[0];
    int row = coordinates[1];
    int tipo;
    if (col == 1 && row == 4) {
      tipo = 301;
    } else if (col == 1 && row == 3) {
      tipo = 303;
    } else if (col == 2 && row == 5) {
      tipo = 309;
    } else if (col == 1 && row == 2) {
      tipo = 302;
    } else if (col == 1 && row == 5) {
      tipo = 310;
    } else if (col == 1 && row == 1) {
      tipo = 305;
    } else if (col == 2 && row == 6) {
      tipo = 311;
    } else if (col == 2 && row == 4) {
      tipo = 308;
    } else if (col == 2 && row == 3) {
      tipo = 307;
    } else if (col == 1 && row == 6) {
      tipo = 306;
    } else if (col == 2 && row == 2) {
      tipo = 312;
    } else {
      tipo = 304;
    }
    QString path(PathFactory().getTilePath(tipo).c_str());
    tile_item* tile = new class tile_item(path, tipo, false);
    return tile;
}
