#include "tile.h"
#include "tiles_container.h"
#include <QString>
#include <vector>
#include "tile_factory.h"
#include "tileset.h"
#include <QImage>
#include <QPainter>
#include <QBrush>

#include "iostream"

#define COL 2
#define WIDTH_CONTAINER 151
#define HEIGHT_CONTAINER 501
#define WIDTH 148
#define ROW_HEIGHT 60

tiles_container::tiles_container(QString path, int cant_row, tile_factory* factory)
{
    int height = ROW_HEIGHT*cant_row;
    QImage image = (new QImage(path))->scaled(WIDTH, height);
    this->label = new QLabel();
    tileset ts(image, COL, cant_row);
    ts.copy_to_label(label);
    this->addWidget(label, Qt::AlignCenter);
    this->factory = factory;
    this->cant_rows = cant_row;
    this->margin_horizontal = (WIDTH_CONTAINER - WIDTH) / 2;
    this->margin_vertical = (HEIGHT_CONTAINER - height) / 2;
}

tile* tiles_container::tile_clicked(int x, int y){
    if(is_inside(x, y)){
        std::vector<int> coordinates = get_tile_coordinate(x, y);
        return this->factory->get_tile(coordinates);
    }
    return NULL;
}

std::vector<int> tiles_container::get_tile_coordinate(int x, int y){

    std::vector<int> coordinates = {};

    float col_width = this->label->pixmap()->width() / COL;
    float row_height = this->label->pixmap()->height() / this->cant_rows;

    for(int i = 1; i <= COL; i++){
        float newColLine = i * col_width + this->margin_horizontal;
        if(x < newColLine ){
            coordinates.push_back(i);
            break;
        }
    }
    for(int i = 1; i <= cant_rows; i++){
        float newRowLine = i * row_height + this->margin_vertical;
        if(y < newRowLine){
            coordinates.push_back(i);
            break;
        }
    }
    return coordinates;
}

bool tiles_container::is_inside(int x, int y){
    if(x < this->margin_horizontal || x > WIDTH_CONTAINER - this->margin_horizontal){
        return false;
    }
    if(y < this->margin_vertical || y > HEIGHT_CONTAINER - this->margin_vertical){
        return false;
    }
    return true;
}

