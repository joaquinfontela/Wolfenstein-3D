#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include "string.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow {
  Q_OBJECT

 public:
  Login(std::string& host, std::string& ip, int& game_id);
  ~Login();

 private slots:
  void on_button_join_clicked();
  void on_button_create_clicked();

 private:
  Ui::Login* ui;
  std::string& my_host;
  std::string& my_ip;
  int& my_game_id;
};
#endif  // LOGIN_H
