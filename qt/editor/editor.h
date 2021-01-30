#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

#include "map_painter.h"
#include "map_canvas.h"
#include "tile.h"
#include "tiles_container.h"
#include "my_map.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow {
  Q_OBJECT

 public:
  tile* tile_selected;
  tiles_container* tile_container;
  map_canvas* mc;
  QWidget* map_container;
  std::vector<int> tile_sizes;
  int actual_tiles_size_index;

  Editor(QWidget* parent = nullptr);
  void initialize_tile_container();
  void initialize_map_container(int col, int row);
  int actual_tile_size();
  void remove_Layout (QWidget* widget);
  void update_map_container(my_map& map);
  ~Editor();

 private slots:
  void on_actionEXIT_triggered();

  void on_actionNew_triggered();

  void on_actionParedes_triggered();

  void on_actionPuertas_triggered();

  void on_actionBorrador_triggered();

  void on_actionDecoraciones_triggered();

  void on_actionItems_triggered();

  void on_actionZoom_in_triggered();

  void on_actionZoom_out_triggered();

 private:
  Ui::Editor* ui;
  void update_container(tiles_container* container);
  void repaint_map();
  std::vector<std::string> maps_saved;
};
#endif  // EDITOR_H
