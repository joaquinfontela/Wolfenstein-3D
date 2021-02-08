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
    explicit join_window(QWidget *parent = nullptr, uint32_t& lobbyID = -1, std::vector<int> availableMatches = {});
    ~join_window();
    uint32_t& match_id;

private slots:
    void on_join_button_clicked();

private:
    Ui::join_window *ui;
};

#endif // JOIN_WINDOW_H
