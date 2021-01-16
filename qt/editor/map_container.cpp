#include "map_container.h"
#include "map_actions.h"
#include <QPainter>
#include <QPen>
#include <QLabel>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QImage>
#include "tile.h"

#define SIDE_SIZE 40

map_container::map_container(int col, int row)
{
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

    QLabel* label = new QLabel();
    label->setPixmap(pm);
    QHBoxLayout* ly = new QHBoxLayout();
    ly->addWidget(label, Qt::AlignCenter);
    this->setLayout(ly);
    this->show();
}

void map_container:: paintEvent(QPaintEvent *event, tile* tile)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}
