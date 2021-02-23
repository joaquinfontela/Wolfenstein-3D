#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

#include "QGraphicsScene"
#include "map_canvas.h"
#include "map_painter.h"
#include "map_scene.h"
#include "tile_item.h"
#include "tiles_container.h"

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
  map_scene* my_map_scene;
  tiles_container* tiles_container_scene;
  bool eraser_on;
  bool only_view_mode;

  Editor(QWidget* parent = nullptr);
  /**
   * @brief Initializes an empty tile container.
   */
  void initialize_tile_container();

  /**
   * @brief Initializes a map container with a grid.
   *
   * @param col the number of columns of the grid.
   * @param row the number of rows of the grid.
   */
  void initialize_map_container(int col, int row);

  /**   *
   * @return the size of the tiles represented in the screen.
   */
  int actual_tile_size();

  ~Editor();

 private slots:

  /**
   * @brief Specifies what has to be done when pressing the EXIT button (in this
   * case, closing the window).
   */
  void on_actionEXIT_triggered();

  /**
   * @brief Specifies what has to be done when pressing the NEW button (in this
   * case, creating a new map).
   */
  void on_actionNew_triggered();

  /**
   * @brief Specifies what has to be done when pressing the PAREDES button (in
   * this case, it shows the walls menu).
   */
  void on_actionParedes_triggered();

  /**
   * @brief Specifies what has to be done when pressing the PUERTAS button (in
   * this case, it shows the doors menu).
   */
  void on_actionPuertas_triggered();

  /**
   * @brief Specifies what has to be done when pressing the BORRADOR button (in
   * this case, it activates the tile item eraser).
   */
  void on_actionBorrador_triggered();

  /**
   * @brief Specifies what has to be done when pressing the DEORAIONES button
   * (in this case, it shows the decorations menu).
   */
  void on_actionDecoraciones_triggered();

  /**
   * @brief Specifies what has to be done when pressing the ITEMS button (in
   * this case, it shows the items menu).
   */
  void on_actionItems_triggered();

  /**
   * @brief Specifies what has to be done when pressing the ZOOM IN button (in
   * this case, it zooms in the editor).
   */
  void on_actionZoom_in_triggered();

  /**
   * @brief Specifies what has to be done when pressing the ZOOM OUT button (in
   * this case, it zooms out the editor).
   */
  void on_actionZoom_out_triggered();

  /**
   * @brief Specifies what has to be done when pressing the OPEN button.
   */
  void on_actionOpen_triggered();

  /**
   * @brief Specifies what has to be done when pressing the SAFE button.
   */
  void on_actionsafe_triggered();

  /**
   * @brief Specifies what has to be done when pressing the RESPAWN button.
   */
  void on_actionRespawn_triggered();

  /**
   * @brief Specifies what has to be done when pressing the SAVE AND EXIT
   * button.
   */
  void on_actionSave_and_exit_triggered();

  /**
   * @brief Specifies what has to be done when pressing the PAREDES FALSAS.
   */
  void on_actionParedes_Falsas_triggered();

  /**
   * @brief Specifies what has to be done when pressing the SAVE AS.
   */
  void on_actionSave_as_triggered();

 private:
  /**
   * @brief Return an empty matrix with mapDimensions dimensions.
   */
  void save_map();

  bool actual_map_saved;

  /**
   * @brief Paints the map.
   */
  void paint_map();

  std::vector<int> tile_sizes;
  int actual_tiles_size_index;
};
#endif  // EDITOR_H
