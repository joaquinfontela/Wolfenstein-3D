#ifndef MATCH_ID_H
#define MATCH_ID_H

#include <QPushButton>

#include "join_window.h"

/**
 * @brief Match id and join window wrapper.
 *
 */
class match_id : public QPushButton {
  Q_OBJECT
 private:
  join_window* my_window;
  int my_match_id;
 private slots:
  void set_match_id();

 public:
  match_id(join_window* my_window, int id);
};

#endif  // MATCH_ID_H
