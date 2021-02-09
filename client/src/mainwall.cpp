#include <QApplication>

#include "../includes/client.h"
#include "../includes/clientprotocol.h"
#include "../../common/includes/Socket/SocketCommunication.h"
#include "./Login/login.h"

int main(int argc, char** argv) {
  int map_id;
  int player_id;
  SocketCommunication socket(-1);


  QApplication a(argc, argv);
  Login w(player_id, map_id, socket);
  w.show();
  a.exec();
  w.hide();

  
 
  Client client(socket);
  std::string mapFile = "../../common/src/YAML/Maps/map";
  mapFile = mapFile + std::to_string(map_id) + ".yaml";

  return client.run(player_id, mapFile);
}
