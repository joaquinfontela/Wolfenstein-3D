#include "editor.h"
#include "ui_editor.h"
#include "tile_container.h"
#include "mousetileactions.h"
#include "empty_tile_container.h"
#include "map_actions.h"
#include "QPainter"
#include "QPen"
#include "size_window.h"
#include "my_map.h"
#include "tiles_container.h"
#include "wall_tile_factory.h"
#include "item_tile_factory.h"
#include "decoration_tile_factory.h"
#include "door_tile_factory.h"

#define SIDE_SIZE 40

void Editor::initialize_tile_container(){
    ui->element_container->setFrameStyle(QFrame::Box);
    mouseTileActions* ef = new mouseTileActions(this);
    ui->element_container->installEventFilter(ef);
    this->tile_container = NULL;
}

void Editor::initialize_map_container(int col, int row){
    my_map* map = new my_map(col, row, this);
    QHBoxLayout* ly = new QHBoxLayout();
    ly->addWidget(map, Qt::AlignCenter);
    ui->map_container->setLayout(ly);
    ui->map_container->show();
    this->map_container = ui->map_container;
    this->mc = new map_canvas(col, row);

    map_actions* ma = new map_actions(this, map);
    ui->map_container->installEventFilter(ma);
}

Editor::Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Editor)
{
    ui->setupUi(this);
    initialize_tile_container();
    ui->map_scroll->setWidgetResizable(true);
}

Editor::~Editor()
{
    delete ui;
}


void Editor::on_actionEXIT_triggered()
{
    QApplication::quit();
}


void Editor::on_actionNew_triggered()
{
    size_window sw(this);
    sw.setModal(true);
    sw.exec();
}

void Editor::update_container(tiles_container* container){
    this->tile_container = container;
    ui->element_container->setLayout(container);
    ui->element_container->show();
}

void Editor::on_actionParedes_triggered()
{
    tile_factory* factory = new wall_tile_factory();
    tiles_container* container = new tiles_container(":/game_element/elementos_mapa/paredes.png", 8, 501, factory);
    update_container(container);
}

void Editor::on_actionPuertas_triggered()
{
    tile_factory* factory = new door_tile_factory();
    tiles_container* container = new tiles_container(":/game_element/elementos_mapa/paredes.png", 8, 501, factory);
    update_container(container);
}

void Editor::on_actionBorrador_triggered()
{
    this->tile_selected = new tile(":/varios/fondo_blanco.png", 0, false);
}

void Editor::on_actionDecoraciones_triggered()
{
    tile_factory* factory = new decoration_tile_factory();
    tiles_container* container = new tiles_container(":/game_element/elementos_mapa/paredes.png", 8, 501, factory);
    update_container(container);
}

void Editor::on_actionItems_triggered()
{
    tile_factory* factory = new item_tile_factory();
    tiles_container* container = new tiles_container(":/game_element/elementos_mapa/paredes.png", 8, 501, factory);
    update_container(container);
}
