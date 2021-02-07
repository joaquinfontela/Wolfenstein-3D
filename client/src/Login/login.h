#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include "../../client/includes/client.h"
#include "string.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Construct a new Login object. Sets the styles for the buttons.
   *
   * @param host Port to connect to.
   * @param ip Ip to connect to.
   * @param game_id Match id.
   */
  Login(std::string& host, std::string& ip, int& game_id);
  ~Login();

 private slots:

  /**
   * @brief Parses the data and joins the given match on a join match event.
   *
   */
  void on_button_join_clicked();

  /**
   * @brief Parses the data and creates a match on a create match event.
   *
   */
  void on_button_create_clicked();

 private:
  Ui::Login* ui;
  std::string& my_host;
  std::string& my_ip;
  int& my_game_id;
};
#endif  // LOGIN_H
