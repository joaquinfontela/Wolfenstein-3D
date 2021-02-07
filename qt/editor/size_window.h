#ifndef SIZE_WINDOW_H
#define SIZE_WINDOW_H

#include <QDialog>
#include "editor.h"

namespace Ui {
class size_window;
}

class size_window : public QDialog
{
    Q_OBJECT

public:
    explicit size_window(QWidget *parent = nullptr);
    ~size_window();

private slots:
    void on_pushButton_clicked();

private:
    Ui::size_window *ui;
    Editor* editor;

};

#endif // SIZE_WINDOW_H
