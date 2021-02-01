#include "open_window.h"

#include <fstream>

#include "QHBoxLayout"
#include "map_save.h"
<<<<<<< HEAD
#include <fstream>
#include "QScrollArea"
#include "QMessageBox"
#include "editor.h"

#define MAP_NAME_PATH "./maps_names.txt"

open_window::open_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::open_window)
{
    ui->setupUi(this);
    QVBoxLayout* ly = new QVBoxLayout();
    ly->setSpacing(10);
    std::ifstream reader;
    std::string line;
    reader.open(MAP_NAME_PATH, std::ifstream::in);
    while (reader.good()) {
        std::getline(reader, line, '\n');
        if(line.empty()){
            continue;
        }
        map_save* ms = new map_save(this, line);
        ly->addWidget(ms,0,Qt::AlignTop);
=======
#include "tile.h"
#include "ui_open_window.h"

#define MAP_NAME_PATH "./maps_names.txt"

open_window::open_window(QWidget* parent)
    : QDialog(parent), ui(new Ui::open_window) {
  ui->setupUi(this);
  QVBoxLayout* ly = new QVBoxLayout();
  ly->setSpacing(0);
  std::ifstream reader;
  std::string line;
  reader.open(MAP_NAME_PATH, std::ifstream::in);
  while (reader.good()) {
    std::getline(reader, line, '\n');
    if (line.empty()) {
      continue;
>>>>>>> 46014885602cd69fc1a9ff3239c8a9d89fc70ede
    }
    map_save* ms = new map_save(this, line);
    ly->addWidget(ms, 0, Qt::AlignTop);
  }
  reader.close();

<<<<<<< HEAD
    ui->map_saved_container->setLayout(ly);
    this->map_selected = NULL;
    this->editor = (Editor*) parent;
}

open_window::~open_window()
{
    delete ui;
}

void open_window::on_open_boton_clicked()
{
    if(this->map_selected == NULL){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No has seleccionado un mapa!!");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
    }else{
    }
}
=======
  ui->map_saved_container->setLayout(ly);
  this->map_selected = NULL;
}

open_window::~open_window() { delete ui; }
>>>>>>> 46014885602cd69fc1a9ff3239c8a9d89fc70ede
