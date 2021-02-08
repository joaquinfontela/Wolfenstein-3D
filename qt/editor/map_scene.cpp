#include "map_scene.h"
#include "QGraphicsScene"
#include <QWidget>
#include <QPainter>
#include <tile_item.h>

#define WHITE_BOX_PATH "./fondo_blanco.png"

map_scene::map_scene(QWidget* parent, int col, int row, int tile_size) : QGraphicsScene(parent){
    this->paint_grill(col, row, tile_size);
}

map_scene::map_scene(QWidget* parent) : QGraphicsScene(parent){}

void map_scene::paint_grill(int col, int row, int tile_size){
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
    this->addPixmap(pm);
    this->setSceneRect(0,0, width, height);
}
