#include <SDL2/SDL.h>

#include <exception>
#include <iostream>
#include <thread>
#include <chrono>

#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Map/Map.h"
#include "../../common/includes/protocol.h"
#include "commandexecuter.h"
#include "commandsender.h"
#include "raycaster.h"
#include "sdlwindow.h"
#include "player.h"
#include "sdltexture.h"
#include "texturemanager.h"
#include <atomic>

#define IMG_PATH "../media/"
#define ERROR -1
#define HEIGHT 600
#define WIDTH 800
#define INVALID_ARGS_ERR "Error, no hostname and/or port given."

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << INVALID_ARGS_ERR << std::endl;
  }
  // Me creo a "window" en el main por si más objetos la quisieran usar.
  SocketCommunication socket(-1);
  socket.connect(argv[1], argv[2]);
  uint32_t protocol = CONNECT_TO_LOBBY;
  uint32_t id_ = 1;  // ID del lobby de la partida.
  uint32_t id;
  uint32_t opcode;

  socket.send(&protocol, sizeof(protocol));
  socket.send(&id_, sizeof(id_));
  socket.receive(&opcode, sizeof(opcode));
  socket.receive(&id, sizeof(id));

//#########################################################
  SdlWindow window(WIDTH, HEIGHT);
  window.fillWolfenstein();

  SdlTexture im1(IMG_PATH "wall.png", window);
  SdlTexture im2(IMG_PATH "wall2.png", window);
  SdlTexture nazit(IMG_PATH "guard.png", window);
  SdlTexture gun(IMG_PATH "chaingun2.png", window);
  SdlTexture back(IMG_PATH "hud.png", window);
  SdlTexture light(IMG_PATH "greenlight.png", window);
  SdlTexture barrel(IMG_PATH "barrel.png", window);
  TextureManager manager;
  manager.loadTexture(1,&im1);
  manager.loadTexture(2,&im2);
  manager.loadTexture(3,&nazit);
  manager.loadTexture(4,&barrel);
  manager.loadTexture(5,&gun);
  manager.loadTexture(6,&back);
  manager.loadTexture(7,&light);
  Map matrix("COMPLETAR CON EL YAML LATER");
  Drawable nazi(6,4,3);
  Drawable barrel1(4,6,4);
  Drawable barrel2(7,7,4);
  Drawable greenlight1(2,5,7);
  Drawable greenlight2(2,7,7);
  std::vector<Drawable> sprites({nazi, barrel1, barrel2, greenlight1, greenlight2});
  std::atomic<bool> alive;
  alive = true;
  Player player(6.0, 4.0, -1.0, 0.0, 0.0, 0.66, 0);
  Raycaster caster(WIDTH, HEIGHT, manager, matrix, alive, &window, &player);
//#########################################################

  int exitcode = 0;
  //CommandSender* sender = new CommandSender(socket);
  //CommandExecuter* worker = new CommandExecuter(id, socket);

  try {
    //worker->start();
    //sender->start();
    caster.run(sprites);
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    exitcode = ERROR;
  }
  alive = false;
  //sender->join();
  //worker->join();
  //delete sender;
  //delete worker;
  return exitcode;
}
