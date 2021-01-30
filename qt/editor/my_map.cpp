#include "my_map.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <vector>
#include "tile.h"

#define WHITE_BOX_PATH "./fondo_blanco.png"

my_map::my_map(/*int col, int row, int tile_size*/) {
  tiles_to_paint = 0;
  //this->paint_grill(col, row, tile_size);
}

void my_map::paint_grill(int col, int row, int tile_size){
    float width = col * tile_size;
    float height = row * tile_size;

    QImage image(WHITE_BOX_PATH);
    QPixmap pm = QPixmap::fromImage(image).scaled(width, height);

    QPainter painter(&pm);
    QPen pen(Qt::black, 0, Qt::SolidLine);
    painter.setPen(pen);

    painter.drawRect(0, 0, width, height);

    for (int i = 0; i <= col; i++) {
      float newH = i * tile_size;
      painter.drawLine(newH - 1, 0, newH - 1, height);
    }

    for (int i = 0; i <= row; i++) {
      float newV = i * tile_size;
      painter.drawLine(0, newV - 1, width, newV - 1);
    }
    this->setPixmap(pm);
    this->my_pm = &pm;
}


void my_map::paintEvent(QPaintEvent* event) {
  if (tiles_to_paint >= 1) {
    QPainter painter(this);
    painter.save();
    QRect rect = event->rect();
    tile* tile = tile_to_paint;
    QImage tile_image = tile->get_image();
    painter.drawImage(rect, tile_image);
    painter.restore();
  } else {
    QLabel::paintEvent(event);
  }
}
