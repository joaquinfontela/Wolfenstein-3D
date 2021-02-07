#ifndef SAVE_WINDOW_H
#define SAVE_WINDOW_H

#include <QDialog>
#include "tile_item.h"
#include "editor.h"

namespace Ui {
class save_window;
}

class save_window : public QDialog
{
    Q_OBJECT

public:
    explicit save_window(QWidget *parent = nullptr);
    ~save_window();

private slots:
    void on_pushButton_clicked();

private:
    Ui::save_window *ui;
    Editor* editor;
};

#endif // SAVE_WINDOW_H
