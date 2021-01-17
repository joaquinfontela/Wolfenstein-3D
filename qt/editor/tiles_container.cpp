#include "tile.h"
#include "tiles_container.h"
#include <QString>
#include <vector>
#include "tile_factory.h"
#include "tileset.h"
#include <QImage>

#define COL 2
#define MARGIN 7
#define WIDTH 134

tiles_container::tiles_container(QString path, int cant_row, int height, tile_factory* factory)
{
    QImage image = (new QImage(path))->scaled(WIDTH, height);
    this->label = new QLabel();
    tileset ts(image, COL, cant_row);
    ts.copy_to_label(label);
    this->addWidget(label);
    this->factory = factory;
    this->cant_rows = cant_row;
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
        float newColLine = i * col_width;
        if(x < newColLine ){
            coordinates.push_back(i);
            break;
        }
    }
    for(int i = 1; i <= cant_rows; i++){
        float newRowLine = i * row_height;
        if(y < newRowLine){
            coordinates.push_back(i);
            break;
        }
    }
    return coordinates;
}

bool tiles_container::is_inside(int x, int y){
    if(x < MARGIN || x > WIDTH - MARGIN){
        return false;
    }
    if(y < MARGIN || y > this->label->pixmap()->height() - MARGIN){
        return false;
    }
    return true;
}
