#include "editor.h"

#include "QPainter"
#include "QPen"
#include "decoration_tile_factory.h"
#include "door_tile_factory.h"
#include "item_tile_factory.h"
#include "map_actions.h"
#include "mousetileactions.h"
#include "my_map.h"
#include "size_window.h"
#include "tiles_container.h"
#include "ui_editor.h"
#include "wall_tile_factory.h"
#include "map_painter.h"
#include <QMessageBox>
#include "open_window.h"
#include "../../common/includes/YAML/YAMLConfigReader.h"
#include "../../common/includes/YAML/YAMLMapReader.h"
#include "../../common/includes/YAML/YAMLMapWriter.h"
#include "save_window.h"
#include "QGraphicsScene"
#include "QGraphicsView"

#define BASE_SIDE_SIZE 40
#define PLUS_SIDE_SIZE 60
#define LARGE_SIDE_SIZE 80
#define WHITE_BOX_PATH "./fondo_blanco.png"
#define WALL_TILESET_PATH "./elementos_mapa/paredes/wall_tileset.png"
#define ITEM_TILESET_PATH "./elementos_mapa/items/items_tileset.png"
#define DECORATION_TILESET_PATH "./elementos_mapa/decoraciones/decoration_tileset.png"
#define DOOR_TILESET_PATH "./elementos_mapa/puertas/door_tileset.png"
#define RESPAWN_ICON_PATH "./elementos_mapa/otros/respawn_icon.png"

void Editor::initialize_tile_container() {
  ui->element_container->setFrameStyle(QFrame::Box);
  mouseTileActions* ef = new mouseTileActions(this);
  ui->element_container->installEventFilter(ef);
  this->tile_container = NULL;
}

void Editor::initialize_map_container(int col, int row) {
  /*graphics_scene = new QGraphicsScene(this);
  QGraphicsView* graphics_view = new QGraphicsView(this);
  graphics_view->setScene(graphics_scene);
  ui->map_scroll->setWidget(graphics_view);*/

  my_map* map = new my_map(col, row, this->actual_tile_size());
  QHBoxLayout* ly = new QHBoxLayout();
  ly->addWidget(map, Qt::AlignCenter);
  ui->map_container->setLayout(ly);
  this->map_container = ui->map_container;
  this->mc = new map_canvas(col, row);
  map_actions* ma = new map_actions(this, *map);
  ui->map_container->installEventFilter(ma);

  ui->actionsafe->setEnabled(true);
}

Editor::Editor(QWidget* parent) : QMainWindow(parent), ui(new Ui::Editor){
  ui->setupUi(this);
  initialize_tile_container();
  ui->map_scroll->setWidgetResizable(true);
  this->tile_selected = NULL;
  this->tile_sizes = {BASE_SIDE_SIZE, PLUS_SIDE_SIZE, LARGE_SIDE_SIZE};
  this->actual_tiles_size_index = 0;
  ui->actionsafe->setEnabled(false);
  this->actual_map_saved = false;
}

Editor::~Editor() { delete ui; }

void Editor:: update_map_container(my_map& map){
    this->remove_Layout(ui->map_container);
    QHBoxLayout* ly = new QHBoxLayout();
    ly->addWidget(&map, Qt::AlignCenter);
    ui->map_container->setLayout(ly);
}

int Editor::actual_tile_size(){
    return this->tile_sizes.at(actual_tiles_size_index);
}

void Editor::on_actionEXIT_triggered() { QApplication::quit(); }

void Editor::on_actionNew_triggered() {
  size_window sw(this);
  sw.setModal(true);
  sw.exec();
}

void Editor::remove_Layout (QWidget* widget)
{
    QLayout* ly = widget->layout ();
    if (ly != 0){
        QLayoutItem *item;
        while ((item = ly->takeAt(0)) != 0){
            ly->removeItem(item);
        }
        delete ly;
    }
}

void Editor::update_container(tiles_container* container) {
  this->tile_container = container;
  remove_Layout(ui->element_container);
  ui->element_container->setLayout(container);
  ui->element_container->show();
}

void Editor::on_actionParedes_triggered() {
  tile_factory* factory = new wall_tile_factory();
  tiles_container* container =
      new tiles_container( WALL_TILESET_PATH , 6, factory);
  update_container(container);
}

void Editor::on_actionPuertas_triggered() {
  tile_factory* factory = new door_tile_factory();
  tiles_container* container =
  new tiles_container(DOOR_TILESET_PATH, 2, factory);
  update_container(container);
}

void Editor::on_actionBorrador_triggered() {
  this->tile_selected = new tile( WHITE_BOX_PATH , 0, false);
}

void Editor::on_actionDecoraciones_triggered() {
  tile_factory* factory = new decoration_tile_factory();
  tiles_container* container =
      new tiles_container(DECORATION_TILESET_PATH, 7, factory);
  update_container(container);
}

void Editor::on_actionItems_triggered() {
  tile_factory* factory = new item_tile_factory();
  tiles_container* container =
      new tiles_container(ITEM_TILESET_PATH, 6, factory);
  update_container(container);
}

void Editor::repaint_map(){
    int col = this->mc->cant_col;
    int row = this->mc->cant_row;
    my_map* map = new my_map(col, row, this->actual_tile_size());
    QHBoxLayout* ly = new QHBoxLayout();
    ly->addWidget(map, Qt::AlignCenter);
    remove_Layout(ui->map_container);
    ui->map_container->setLayout(ly);
    Map_painter* mp = new Map_painter(this->actual_tile_size(), *map);
    mp->paint_all_tiles(this->mc);
}

void Editor::on_actionZoom_in_triggered()
{
    if(actual_tiles_size_index == 0){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Este es el minimo zoom posible");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
    } else{
        this->actual_tiles_size_index--;
        this->repaint_map();
    }
}

void Editor::on_actionZoom_out_triggered()
{
    if(actual_tiles_size_index == 2){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Este es el maximo zoom posible");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
    } else{
        this->actual_tiles_size_index++;
        this->repaint_map();
    }
}

void Editor::on_actionOpen_triggered()
{
    open_window ow(this);
    ow.setModal(true);
    ow.exec();
}

void Editor::save_map(){
    if(actual_map_saved){
        std::string name_path = this->actual_map_name + ".YAML";
        YAMLMapWriter* map_creator = new YAMLMapWriter(name_path);
        TileMatrix matrix = this->mc->grilla;
        map_creator->createYamlMapFile(matrix);
        delete map_creator;
    }else{
        save_window sw(this);
        sw.setModal(true);
        sw.exec();
        actual_map_saved = true;
    }
}

void Editor::on_actionsafe_triggered()
{
    this->save_map();
}

void Editor::on_actionRespawn_triggered()
{
    this->tile_selected = new tile( RESPAWN_ICON_PATH , 0, false);
}

void Editor::on_actionSave_and_exit_triggered()
{
    this->save_map();
    QApplication::quit();
}
