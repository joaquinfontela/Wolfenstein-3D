#include <QApplication>

#include "../includes/client.h"
#include "../includes/clientprotocol.h"
#include "./Login/login.h"

int main(int argc, char** argv) {
  std::string ip;
  std::string port;
  int game_id;
  if (argc == 3) {
    ip = argv[1];
    port = argv[2];
    game_id = 2;
  } else {
    QApplication a(argc, argv);
    Login w(port, ip, game_id);
    w.show();
    a.exec();
    w.hide();
  }

  Client client;
  std::string mapFile = "../../common/src/YAML/map1.yaml";

  return client.run(ip, port, game_id, mapFile);
}
