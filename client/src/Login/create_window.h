#ifndef CREATE_WINDOW_H
#define CREATE_WINDOW_H

#include <QDialog>

namespace Ui {
class create_window;
}

class create_window : public QDialog
{
    Q_OBJECT

public:
    explicit create_window(QWidget *parent);
    ~create_window();
    uint32_t get_map_id();

private slots:
    void on_pushButton_clicked();

private:
    Ui::create_window *ui;
    int my_map_id;
};

#endif // CREATE_WINDOW_H
