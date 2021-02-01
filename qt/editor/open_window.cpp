#include "open_window.h"

#include <fstream>

#include "QHBoxLayout"
#include "map_save.h"
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
    }
    map_save* ms = new map_save(this, line);
    ly->addWidget(ms, 0, Qt::AlignTop);
  }
  reader.close();

  ui->map_saved_container->setLayout(ly);
  this->map_selected = NULL;
}

open_window::~open_window() { delete ui; }
