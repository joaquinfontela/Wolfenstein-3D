#include "tile.h"

#include <QString>

tile::tile(QString path, int tipo, bool cumulative) {
  QImage image(path);
  QPixmap pm = QPixmap::fromImage(image);
  this->label.setPixmap(pm);
  my_image = image;
  this->type = tipo;
  this->cumulative = cumulative;
}

QImage tile::get_image() { return this->my_image; }

bool tile::accept_tile(tile* tile) {
  return this->cumulative && tile->cumulative;
}

int tile::get_type() { return this->type; }