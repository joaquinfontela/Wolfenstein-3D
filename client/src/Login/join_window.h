#ifndef JOIN_WINDOW_H
#define JOIN_WINDOW_H

#include <QDialog>

namespace Ui {
class join_window;
}

class join_window : public QDialog
{
    Q_OBJECT

public:
    explicit join_window(QWidget *parent = nullptr);
    ~join_window();

private:
    Ui::join_window *ui;
};

#endif // JOIN_WINDOW_H
