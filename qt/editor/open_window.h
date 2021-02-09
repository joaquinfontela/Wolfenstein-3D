#ifndef OPEN_WINDOW_H
#define OPEN_WINDOW_H

#include <QDialog>
#include "tile_item.h"
#include "editor.h"

namespace Ui {
class open_window;
}

class open_window : public QDialog
{
    Q_OBJECT

public:
    explicit open_window(QWidget *parent, bool* map_was_changed);
    ~open_window();
     std::vector<std::vector<std::vector<tile_item*>>>* map_selected;
     std::string map_name;
private slots:
     void on_open_boton_clicked();

private:
    Ui::open_window *ui;
    Editor* editor; 
    bool* map_was_changed;
};

#endif // OPEN_WINDOW_H
