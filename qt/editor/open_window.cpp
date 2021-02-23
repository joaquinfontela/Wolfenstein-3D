#include "open_window.h"

#include <fstream>

#include "QHBoxLayout"
#include "QMessageBox"
#include "QScrollArea"
#include "editor.h"
#include "iostream"
#include "map_actions.h"
#include "map_canvas.h"
#include "map_save.h"
#include "tile_item.h"
#include "ui_editor.h"
#include "ui_open_window.h"

#define MAP_NAME_PATH "./maps/maps_names.txt"

open_window::open_window(QWidget* parent, bool* map_was_changed)
    : QDialog(parent), ui(new Ui::open_window) {
  ui->setupUi(this);
  QVBoxLayout* ly = new QVBoxLayout();
  ly->setSpacing(10);
  std::ifstream reader;
  std::string line;
  reader.open(MAP_NAME_PATH, std::ifstream::in);
  bool is_first_iteration = true;
  map_save* last_ms;
  while (reader.good()) {
    std::getline(reader, line, '\n');
    if (line.empty()) {
      continue;
    }
    map_save* ms = new map_save(this, line);
    if (is_first_iteration) {
      QObject::connect(ly, &QObject::destroyed, ms, &QObject::deleteLater);
      last_ms = ms;
      is_first_iteration = false;
    } else {
      QObject::connect(last_ms, &QObject::destroyed, ms, &QObject::deleteLater);
      last_ms = ms;
    }
    ly->addWidget(ms, 0, Qt::AlignTop);
  }
  reader.close();
  ui->map_saved_container->setLayout(ly);
  this->map_selected = NULL;
  this->editor = (Editor*)parent;
  this->map_was_changed = map_was_changed;
}

open_window::~open_window() {
  delete this->ui->map_saved_container->layout();
  delete ui;
}

void open_window::on_open_boton_clicked() {
  if (this->map_selected == NULL) {
    QMessageBox messageBox;
    messageBox.critical(0, "Error", "No has seleccionado un mapa!!");
    messageBox.setFixedSize(500, 200);
    messageBox.exec();
  } else {
    map_canvas* new_mc = new map_canvas(this->map_selected);
    int cant_rows = new_mc->grilla.size();
    int cant_col = new_mc->grilla.at(0).size();
    if (this->editor->my_map_scene == NULL) {
      editor->my_map_scene = new class map_scene(this->editor);
      editor->ui->graphics_map_container->setScene(editor->my_map_scene);
      map_actions* ma = new map_actions(editor, editor->my_map_scene);
      editor->ui->graphics_map_container->installEventFilter(ma);
      QObject::connect(editor->my_map_scene, &QObject::destroyed, ma,
                       &QObject::deleteLater);
      editor->ui->actionsafe->setEnabled(true);

    } else {
      this->editor->my_map_scene->clear();
    }
    delete this->editor->mc;
    this->editor->mc = new_mc;

    for (int i = 0; i < cant_rows; i++) {
      for (int x = 0; x < cant_col; x++) {
        std::vector<tile_item*> tile_vector =
            this->editor->mc->grilla.at(i).at(x);
        for (size_t y = 0; y < tile_vector.size(); y++) {
          tile_vector.at(y)->add_to(this->editor->ui->graphics_map_container);
        }
      }
    }
    editor->actual_map_name = this->map_name;
    *this->map_was_changed = true;
    this->close();
  }
}
