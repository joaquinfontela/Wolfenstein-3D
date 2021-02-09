#include "tile_item.h"

#include <QApplication>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>

#include "QImage"
#include "iostream"

tile_item::tile_item(std::string path, int tipo, bool cumulative) {
  this->path = path;
  QImage image(QString::fromStdString(path));
  this->my_image = image;
  this->type = tipo;
  this->cumulative = cumulative;
  QRect rect(0, 0, 0, 0);
  this->my_rect = rect;
  this->map = NULL;
}

tile_item* tile_item::create_copy() {
    std::string place_holder = this->path;
  tile_item *tile = new tile_item(place_holder, this->type, this->cumulative);
  if (this->map != NULL) {
    tile->add_to(this->map);
  }
  return tile;
}

void tile_item::add_to(QGraphicsView *map) { this->map = map; }

bool tile_item::accept_tile(tile_item *tile) {
  return this->cumulative && tile->cumulative;
}

int tile_item::get_type() { return this->type; }

void tile_item::configure_rect(int tile_size, float x, float y) {
  if (tile_size != 0) {
    this->my_rect.setWidth(tile_size);
    this->my_rect.setHeight(tile_size);
  }
  if (x != -1 && y != -1) {
    this->my_rect.setCoords(x, y, x + tile_size, y + tile_size);
  }
}

QRectF tile_item::boundingRect() const { return this->my_rect; }

void tile_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
  int tile_size = my_rect.width();
  painter->drawImage(this->my_rect,
                     this->my_image.scaled(tile_size, tile_size));
}


void tile_item::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QPoint p;
  QScrollBar *vertical_bar = this->map->verticalScrollBar();
  QScrollBar *horizontal_bar = this->map->horizontalScrollBar();
  p.setX(event->pos().x() - horizontal_bar->value());
  p.setY(event->pos().y() - vertical_bar->value());
  QMouseEvent me(QEvent::MouseButtonPress, p, Qt::MouseButton::LeftButton,
                      Qt::MouseButton::AllButtons, 0);
  QApplication::sendEvent(this->map, &me);
}

void tile_item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
