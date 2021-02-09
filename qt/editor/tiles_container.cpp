#include "tiles_container.h"
#include <QString>
#include <vector>
#include "tile_factory.h"
#include <QImage>
#include <QPainter>
#include <QBrush>
#include "tile_item.h"
#include <QGraphicsScene>
#include <QPointer>

#include "iostream"

#define COL 2
#define HEIGHT_CONTAINER 501
#define WIDTH 148
#define ROW_HEIGHT 60

tiles_container::tiles_container(QString path, int cant_row, tile_factory* factory)
{
    this->pm_item = NULL;
    update_tileset(path, cant_row, factory);   
}

tiles_container::tiles_container(){
    this->pm_item = NULL;
    this->factory = NULL;
}

tiles_container::~tiles_container()
{
    delete this->pm_item;
    delete this->factory;
}

bool tiles_container::is_empty()
{
    if(this->pm_item == NULL){
        return true;
    }
    return false;
}

void tiles_container::update_tileset(QString path, int cant_row, tile_factory *factory){

    int height = ROW_HEIGHT*cant_row;
    this->cant_rows = cant_row;
    this->margin_vertical = HEIGHT_CONTAINER - height;

    if(this->pm_item != NULL){
        delete this->pm_item;
        delete this->factory;
    }

    this->factory = factory;
    QPixmap* pm = new QPixmap(path);
    QPixmap pm_scaled = pm->scaled(WIDTH, height);


    QPainter painter(&pm_scaled);
    QPen pen(Qt::black, 0, Qt::SolidLine);
    painter.setPen(pen);

    float col_width = WIDTH/2;
    painter.drawRect(0,0, WIDTH-1, height-1);


    for(int i = 1; i < COL; i++){
        float newH = i * col_width;
        painter.drawLine(newH, 0, newH, height);
    }

    for(int i = 1; i < cant_row; i++){
        float newV = i * ROW_HEIGHT;
        painter.drawLine(0, newV, WIDTH, newV);
    }
    QGraphicsPixmapItem* pm_ = new QGraphicsPixmapItem(pm_scaled);
    this->addItem(pm_);
    this->pm_item = pm_;
    delete pm;
}


tile_item* tiles_container::tile_clicked(int x, int y){
    if(is_inside(x, y)){
        std::vector<int> coordinates = get_tile_coordinate(x, y);
        return this->factory->get_tile(coordinates);
    }
    return NULL;
}

std::vector<int> tiles_container::get_tile_coordinate(int x, int y){

    std::vector<int> coordinates = {};

    float col_width = WIDTH / COL;
    float row_height = this->pm_item->pixmap().height() / this->cant_rows;

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
    if(y > HEIGHT_CONTAINER - this->margin_vertical){
        return false;
    }
    return true;
}

