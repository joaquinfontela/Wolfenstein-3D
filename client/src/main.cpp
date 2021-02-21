#include <atomic>
#include <QApplication>

#include "../includes/client.h"
#include "../includes/clientprotocol.h"
#include "../../common/includes/Socket/SocketCommunication.h"
#include "./Login/login.h"

int main(int argc, char** argv) {

  std::atomic<bool> endingGame;
  std::atomic<bool> restart;

  while (true) {
    endingGame = true;
    restart = false;
    int map_id;
    int player_id;
    SocketCommunication socket;

    QApplication a(argc, argv);
    Login w(player_id, map_id, socket, endingGame, restart);
    w.show();
    a.exec();
    w.hide();

    if (restart) continue;
    if (endingGame) break;

    Client client(socket, player_id);
    std::string mapFile = "/usr/local/share/Wolfenstein/YAML/Maps/map";
    mapFile = mapFile + std::to_string(map_id) + ".yaml";

    client.run(mapFile);
  }
}
