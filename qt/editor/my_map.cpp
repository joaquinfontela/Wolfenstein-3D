#include "my_map.h"

#include <QPen>
#include <QPainter>
#include "tile.h"
#include <vector>
#include "editor.h"
#include <QPaintEvent>

#define SIDE_SIZE 40

my_map::my_map(int col, int row, Editor* editor)
{
    this->print_tile = false;
    float width = col*SIDE_SIZE;
    float height = row*SIDE_SIZE;

    QImage image(":/varios/fondo_blanco.png");
    QPixmap pm = QPixmap::fromImage(image).scaled(width, height);

    QPainter painter(&pm);
    QPen pen(Qt::black, 0, Qt::SolidLine);
    painter.setPen(pen);

    painter.drawRect(0,0, width, height);

    for(int i = 0; i <= col; i++){
        float newH = i * SIDE_SIZE;
        painter.drawLine(newH-1, 0, newH-1, height);
    }

    for(int i = 0; i <= row; i++){
        float newV = i * SIDE_SIZE;
        painter.drawLine(0, newV-1, width, newV-1);
    }

    this->editor = editor;
    this->setPixmap(pm);
}


void my_map::paintEvent(QPaintEvent *event){
    if(print_tile){
        QPainter painter(this);
        QRect rect = event->rect();
        tile* tile = this->editor->tile_selected;
        QImage tile_image = tile->get_image().scaled(SIDE_SIZE, SIDE_SIZE);
        painter.drawImage(rect, tile_image);
    } else {
        QLabel::paintEvent(event);
    }
}

