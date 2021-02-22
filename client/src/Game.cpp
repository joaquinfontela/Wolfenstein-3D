#include "../includes/Game.h"
#define MAP_NOT_FOUND_ERROR "Error, map not found: "
#define COULD_NOT_CREATE_EXECUTER "Fatal error, the executer couldn't be created."
#define COULD_NOT_CREATE_SENDER "Fatal error, the sender couldn't be created."
#define MAX_NUMBER_OF_TEXTURES_PER_FRAME 100

Game::Game(SocketCommunication& socket, SdlWindow* window, uint32_t myPlayerID, std::string& mapFile) :
 manager(window), scoreboard(manager), starting(manager), players(myPlayerID), loader(mapFile), socket(socket){
  this->myPlayerID = myPlayerID;
}

int Game::start(){
  std::atomic<bool> alive;
  alive = true;

  Hud hud(players.getSelf(), manager, audios);
  std::vector<Drawable*> sprites = loader.getDrawableItemList();
  sprites.reserve(MAX_NUMBER_OF_TEXTURES_PER_FRAME);
  DrawableVector spriteVector(sprites);
  Map matrix(loader);

  Raycaster caster(manager, matrix, alive, players.getSelf(), spriteVector, hud, starting);
  CommandSender* sender = new CommandSender(socket, alive, &scoreboard, players.getSelf(), &starting);
  CommandExecuter* worker = new CommandExecuter(socket, alive, spriteVector, players, myPlayerID, audios, matrix, loader, &scoreboard, starting);
  int exitcode = 0;

  if (!sender) {
    throw std::runtime_error(COULD_NOT_CREATE_SENDER);
  } else if (!worker) {
    throw std::runtime_error(COULD_NOT_CREATE_EXECUTER);
  }

  try {
    worker->start();
    sender->start();
    caster.run();
    scoreboard.draw();
  } catch (std::exception& e) {
    LOG(e.what());
    exitcode = ERROR;
  }
  alive = false;
  sender->join();
  worker->join();
  delete sender;
  delete worker;
  return exitcode;
}
