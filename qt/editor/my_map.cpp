#include "my_map.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <vector>

#include "editor.h"
#include "tile.h"

#define SIDE_SIZE 40

my_map::my_map(int col, int row) {
  float width = col * SIDE_SIZE;
  float height = row * SIDE_SIZE;

  QImage image("./fondo_blanco.png");
  QPixmap pm = QPixmap::fromImage(image).scaled(width, height);

  QPainter painter(&pm);
  QPen pen(Qt::black, 0, Qt::SolidLine);
  painter.setPen(pen);

  painter.drawRect(0, 0, width, height);

  for (int i = 0; i <= col; i++) {
    float newH = i * SIDE_SIZE;
    painter.drawLine(newH - 1, 0, newH - 1, height);
  }

  for (int i = 0; i <= row; i++) {
    float newV = i * SIDE_SIZE;
    painter.drawLine(0, newV - 1, width, newV - 1);
  }
  this->setPixmap(pm);
  tiles_to_paint = 0;
}

void my_map::paintEvent(QPaintEvent* event) {
  if (tiles_to_paint >= 1) {
    QPainter painter(this);
    QRect rect = event->rect();
    tile* tile = tile_to_paint;
    QImage tile_image = tile->get_image();
    painter.drawImage(rect, tile_image);
  } else {
    QLabel::paintEvent(event);
  }
}
