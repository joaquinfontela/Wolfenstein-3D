#include <QApplication>

#include "iostream"
#include "login.h"
#include "string.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  std::string ip;
  std::string host;
  int game_id;
  Login w(host, ip, game_id);
  w.show();
  a.exec();
  return 0;
}
