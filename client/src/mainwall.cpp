#include <SDL2/SDL.h>

#include <exception>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Map/Map.h"
#include "../../common/includes/protocol.h"
#include "commandexecuter.h"
#include "commandsender.h"
#include "raycaster.h"
#include "sdlwindow.h"
#include "player.h"
#include "hud.h"
#include "sdltexture.h"
#include "texturemanager.h"
#include "audiomanager.h"
#include "clientprotocol.h"
#include "ClientMapLoader.h"

#define ERROR -1
#define INVALID_ARGS_ERR "Error, no hostname and/or port given."

static void deleteSprites(std::vector<Drawable*>& sprites) {
  for (Drawable* s : sprites) {
    if (s->isSprite()) delete s;
  }
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << INVALID_ARGS_ERR << std::endl;
  }
  SdlWindow window(WIDTH, HEIGHT);
  // Me creo a "window" en el main por si más objetos la quisieran usar.
  SocketCommunication socket(-1);
  socket.connect(argv[1], argv[2]);
  uint32_t protocol = CONNECT_TO_LOBBY;
  uint32_t id_ = 2;  // ID del lobby de la partida.
  uint32_t id;
  uint32_t opcode;

  std::mutex m;
  socket.send(&protocol, sizeof(protocol));
  socket.send(&id_, sizeof(id_));
  socket.receive(&opcode, sizeof(opcode));
  socket.receive(&id, sizeof(id));
  std::string mapFile = "../../common/src/YAML/map.yaml";
  ClientMapLoader loader(mapFile, 24, 24);
  Map matrix(loader);

  TextureManager manager(&window);
  manager.loadTextures();
  AudioManager audios;

  std::atomic<bool> alive;
  alive = true;
  Player* player = new Player(6.0, 4.0, -1.0, 0.0, 0.0, 0.66, 0);
  Hud hud(&window, player, manager);
  std::map<uint32_t,Player*> players;
  players[id] = player;

  std::cout << "[CLIENT] My id is: " << id << std::endl;

  std::vector<Drawable*> sprites = loader.getDrawableItemList(); // Falta tener bien los ids de los sprites.

  Raycaster caster(manager, matrix, alive, &window, player, sprites, m, hud);
  int exitcode = 0;
  CommandSender* sender = new CommandSender(socket, alive);
  CommandExecuter* worker = new CommandExecuter(socket, alive, sprites, players, m, id, audios, matrix);

  try {
    worker->start();
    sender->start();
    caster.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    exitcode = ERROR;
  }
  alive = false;
  sender->join();
  worker->join();
  delete player;
  delete sender;
  delete worker;
  deleteSprites(sprites);
  return exitcode;
}
