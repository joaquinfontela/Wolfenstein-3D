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
 // w.show();
 // a.exec();
 // w.hide();
 
  std::string host = "localhost";
  std::string port = "8080";

  socket.connect(host, port);
  uint32_t opcode = CREATE_LOBBY;
  uint32_t map_id1 = 123;
  uint32_t ID = -1;

  socket.send(&opcode, sizeof(opcode));
  socket.send(&map_id1, sizeof(map_id1));

  socket.receive(&opcode, sizeof(opcode));
  socket.receive(&ID, sizeof(ID));

  map_id = map_id1;
  player_id = ID;

  Client client(socket);
  std::string mapFile = "../../common/src/YAML/map";
  mapFile = mapFile + std::to_string(map_id) + ".yaml";

  return client.run(player_id, mapFile);
}
