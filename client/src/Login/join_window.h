#ifndef JOIN_WINDOW_H
#define JOIN_WINDOW_H

#include <QDialog>

namespace Ui {
class join_window;
}

/**
 * @brief Qt window with all the available matches to join.
 *
 */
class join_window : public QDialog {
  Q_OBJECT

 public:
  /**
   * @brief Construct a new join window object
   *
   * @param parent
   * @param availableMatches
   */
  explicit join_window(QWidget *parent, std::vector<int> availableMatches);
  ~join_window();
  int my_match_id;

  /**
   * @brief Get the match id.
   *
   * @return uint32_t match id.
   */
  uint32_t get_match_id();
 private slots:

  /**
   * @brief Handler for the join button press event. Stores the id, throws an
   * error pop-up if it any errors happen.
   *
   */
  void on_join_button_clicked();

 private:
  Ui::join_window *ui;
};

#endif  // JOIN_WINDOW_H
