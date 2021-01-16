#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include "tile.h"
#include "tiles_container.h"
#include "map_canvas.h"
#include "map_container.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    tile* tile_selected;
    tiles_container* tile_container;
    map_canvas* mc;
    QWidget* map_container;

    Editor(QWidget *parent = nullptr);
    void initialize_tile_container();
    void initialize_map_container(int col, int row);
    ~Editor();

private slots:
    void on_actionEXIT_triggered();

    void on_actionNew_triggered();

    void on_actionParedes_triggered();

    void on_actionPuertas_triggered();

    void on_actionBorrador_triggered();

    void on_actionDecoraciones_triggered();

    void on_actionItems_triggered();

private:
    Ui::Editor *ui;
    void update_container(tiles_container* container);
};
#endif // EDITOR_H
