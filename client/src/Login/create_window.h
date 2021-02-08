#ifndef CREATE_WINDOW_H
#define CREATE_WINDOW_H

#include <QDialog>

namespace Ui {
class create_window;
}

/**
 * @brief Qt window to choose the map number to play.
 *
 */
class create_window : public QDialog {
  Q_OBJECT

 public:
  explicit create_window(QWidget *parent);
  ~create_window();

  /**
   * @brief Get the map id.
   *
   * @return uint32_t match id.
   */
  uint32_t get_map_id();

 private slots:

  /**
   * @brief Handler for the button click event. Stores the id, throws an error
   * pop-up if it any errors happen.
   *
   */
  void on_pushButton_clicked();

 private:
  Ui::create_window *ui;
  int my_map_id;
};

#endif  // CREATE_WINDOW_H
