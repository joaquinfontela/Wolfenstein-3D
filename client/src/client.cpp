#include "../includes/client.h"

#include "../includes/clientprotocol.h"
#include "../includes/log.h"
#include "../includes/scoreboard.h"

#define MAX_NUMBER_OF_TEXTURES_PER_FRAME 100

void Client::gargabeCollector(std::vector<Drawable*>& sprites) {
  for (Drawable* s : sprites) {
    delete s;
  }
}

void Client::connectToServer(std::string& ip, std::string& port) {
  this->socket.connect(ip, port);
}

bool Client::joinMatch(uint32_t lobbyID) {
  uint32_t protocol = CONNECT_TO_LOBBY;
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

int Client::run(std::string& ip, std::string& port, uint32_t lobbyID,
                std::string& mapFile) {
  this->connectToServer(ip, port);

  if (!this->joinMatch(lobbyID)) {
    return ERROR;
  }

  SdlWindow window(WIDTH, HEIGHT);
  ClientMapLoader loader(mapFile, 24, 24);
  Map matrix(loader);

  TextureManager manager(&window);
  manager.loadTextures();
  AudioManager audios;

  std::mutex m;
  ScoreBoard scoreboard(&window);

  std::atomic<bool> alive;
  alive = true;
  Player* player = new Player(3.0, 3.0, -1.0, 0.0, 0.0, 0.66, 0);
  Hud hud(player, manager, audios);
  std::map<uint32_t, Player*> players;
  players[this->myPlayerID] = player;

  std::cout << "[CLIENT] Player Succesfully connected with ID: " << myPlayerID
            << std::endl;

  std::vector<Drawable*> sprites = loader.getDrawableItemList();
  sprites.reserve(MAX_NUMBER_OF_TEXTURES_PER_FRAME);

  Raycaster caster(manager, matrix, alive, &window, player, sprites, m, hud,
                   scoreboard);
  int exitcode = 0;
  CommandSender* sender = new CommandSender(socket, alive, &scoreboard);
  CommandExecuter* worker =
      new CommandExecuter(socket, alive, sprites, players, m, myPlayerID,
                          audios, matrix, loader, scoreboard);

  try {
    worker->start();
    sender->start();
    caster.run();
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
