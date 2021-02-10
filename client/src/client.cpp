#include "../includes/client.h"

#include "../includes/clientprotocol.h"
#include "../includes/drawablevector.h"
#include "../includes/log.h"
#include "../includes/scoreboard.h"
#include "../includes/configReader.h"

#include <exception>

#define MAP_NOT_FOUND_ERROR "Error, map not found: "
#define COULD_NOT_CREATE_EXECUTER "Fatal error, the executer couldn't be created."
#define COULD_NOT_CREATE_SENDER "Fatal error, the sender couldn't be created."
#define MAX_NUMBER_OF_TEXTURES_PER_FRAME 100

static bool fileExists(std::string& name){
  if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void Client::gargabeCollector(std::vector<Drawable*>& sprites) {
  for (Drawable* s : sprites) {
    delete s;
  }
}

void Client::connectToServer(std::string& ip, std::string& port) {
  this->socket.connect(ip, port);
}

bool Client::joinMatch(uint32_t lobbyID) {
  uint32_t protocol = CREATE_LOBBY;
  uint32_t opcode;
  uint32_t selfID;

  // Connection Request
  socket.send(&protocol, sizeof(protocol));
  socket.send(&lobbyID, sizeof(lobbyID));

  // Connection Response
  socket.receive(&opcode, sizeof(opcode));

  if (opcode != CONNECTED_OK) return false;

  socket.receive(&selfID, sizeof(selfID));
  this->myPlayerID = selfID;
  Log::playerId = selfID;

  return true;
}

int Client::run(int myPlayerID, std::string& mapFile) {

  if(myPlayerID == -1){
    return ERROR;
  }

  if(!fileExists(mapFile)){
    std::string error = MAP_NOT_FOUND_ERROR + mapFile;
    LOG(error.c_str());
    return ERROR;
  }

  ConfigReader config("../YAMLConfig/screenDimensions.yaml");
  int height = config.getHeight();
  int width = config.getWidth();

  this->myPlayerID = myPlayerID;

  SdlWindow window(width, height);
  if (config.fullScreen()) {
    window.goFullScreen();
  }

  ClientMapLoader loader(mapFile, 24, 24);
  Map matrix(loader);

  TextureManager manager(&window);
  manager.loadTextures();
  AudioManager audios;

  std::mutex m;
  ScoreBoard scoreboard(manager);

  std::atomic<bool> alive;
  alive = true;
  Player* player = new Player(3.0, 3.0, -1.0, 0.0, 0.0, 0.66, 0);

  if (!player) {
    throw std::runtime_error(COULD_NOT_CREATE_PLAYER);
  }

  Hud hud(player, manager, audios);
  std::map<uint32_t, Player*> players;
  players[this->myPlayerID] = player;

  std::vector<Drawable*> sprites = loader.getDrawableItemList();
  sprites.reserve(MAX_NUMBER_OF_TEXTURES_PER_FRAME);

  DrawableVector spriteVector(sprites, m);

  Raycaster caster(manager, matrix, alive, player, spriteVector, hud);
  int exitcode = 0;
  CommandSender* sender = new CommandSender(socket, alive, &scoreboard, player);
  CommandExecuter* worker =
      new CommandExecuter(socket, alive, spriteVector, players, myPlayerID,
                          audios, matrix, loader, &scoreboard);

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
  delete player;
  delete sender;
  delete worker;
  this->gargabeCollector(sprites);
  return exitcode;
}
