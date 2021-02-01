#ifndef OPEN_WINDOW_H
#define OPEN_WINDOW_H

#include <QDialog>
#include "tile.h"

namespace Ui {
class open_window;
}

class open_window : public QDialog
{
    Q_OBJECT

public:
    explicit open_window(QWidget *parent);
    ~open_window();
     std::vector<std::vector<std::vector<tile*>>>* map_selected;
private:
    Ui::open_window *ui;
    std::vector<std::string> maps_saved;
};

#endif // OPEN_WINDOW_H
