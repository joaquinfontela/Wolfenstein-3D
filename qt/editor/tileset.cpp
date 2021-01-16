#include "tileset.h"
#include <QPixmap>
#include <QPen>
#include <QImage>
#include <QPainter>
#include <QColor>

#define WIDTH 130
#define HEIGHT 491

tileset::tileset(QImage template_image, int col, int row)
{
        pm = QPixmap::fromImage(template_image);
        QPainter painter(&pm);
        QPen pen(Qt::white, 0, Qt::SolidLine);
        painter.setPen(pen);

        float col_width = WIDTH / col;
        float row_height = HEIGHT / row;
        painter.drawRect(0,0, WIDTH, HEIGHT);

        for(int i = 1; i < col; i++){
            float newH = i * col_width;
            painter.drawLine(newH, 0, newH, HEIGHT);
        }

        for(int i = 1; i < row; i++){
            float newV = i * row_height;
            painter.drawLine(0, newV, WIDTH, newV);
        }
}

void tileset::copy_to_label(QLabel* label){
    label->setPixmap(pm);
}

