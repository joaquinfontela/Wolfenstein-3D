#include "tileset.h"
#include <QPixmap>
#include <QPen>
#include <QImage>
#include <QPainter>
#include <QColor>

#define WIDTH 145
#define ROW_HEIGHT 60

tileset::tileset(QImage template_image, int col, int row)
{
        int height = ROW_HEIGHT*row;
        pm = QPixmap::fromImage(template_image).scaled(WIDTH, height);
        QPainter painter(&pm);
        QPen pen(Qt::black, 0, Qt::SolidLine);
        painter.setPen(pen);


        float col_width = WIDTH/2;
        painter.drawRect(0,0, WIDTH-15, height-1);


        for(int i = 1; i < col; i++){
            float newH = i * col_width;
            painter.drawLine(newH, 0, newH, height);
        }

        for(int i = 1; i < row; i++){
            float newV = i * ROW_HEIGHT;
            painter.drawLine(0, newV, WIDTH, newV);
        }
}

void tileset::copy_to_label(QLabel* label){
    label->setPixmap(pm);
}

