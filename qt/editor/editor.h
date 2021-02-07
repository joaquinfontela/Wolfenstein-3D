#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

#include "map_painter.h"
#include "map_canvas.h"
#include "tiles_container.h"
#include "QGraphicsScene"
#include "tile_item.h"
#include "map_scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow {
  Q_OBJECT

 public:
  Ui::Editor* ui;
  std::string actual_map_name;
  tile_item* tile_item_selected;
  map_canvas* mc;
  std::vector<int> tile_sizes;
  int actual_tiles_size_index;
  map_scene* my_map_scene;
  tiles_container* tiles_container_scene;
  bool eraser_on;

  Editor(QWidget* parent = nullptr);
  void initialize_tile_container();
  void initialize_map_container(int col, int row);
  int actual_tile_size();

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

  void on_actionOpen_triggered();

  void on_actionsafe_triggered();

  void on_actionRespawn_triggered();

  void on_actionSave_and_exit_triggered();

  void on_actionParedes_Falsas_triggered();

private:
  void save_map();

  bool actual_map_saved;
  void paint_map();
};
#endif  // EDITOR_H
