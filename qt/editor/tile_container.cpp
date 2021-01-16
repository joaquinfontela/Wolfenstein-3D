#include "tile_container.h"
#include "tile.h"
#include "tileset.h"
#include <QHBoxLayout>

#define WIDTH 151
#define HEIGHT 501

tile_container::tile_container(){
    this->container = new QHBoxLayout();
    this->image = new QLabel();
    this->setBaseSize(WIDTH, HEIGHT);
}

void tile_container::set_tileset(tileset ts){
    ts.copy_to_label(this->image);
    container->addWidget(this->image);
    this->setLayout(container);
}
