#include "client.h"
#define ERROR -1

static void deleteSprites(std::vector<Drawable*>& sprites) {
  for (Drawable* s : sprites) {
    if (s->isSprite()) delete s;
  }
}

void Client::connectToServer(std::string& host, std::string& port){
  this->socket.connect(host, port);
}

bool Client::joinMatch(uint32_t lobbyID){

  uint32_t protocol = CONNECT_TO_LOBBY;
  uint32_t opcode;
  uint32_t selfID;

  // Connection Request
  socket.send(&protocol, sizeof(protocol));
  socket.send(&lobbyID, sizeof(lobbyID));

  // Connection Response
  socket.receive(&opcode, sizeof(opcode));

  if(opcode != CONNECTED_OK)
    return false;

  socket.receive(&selfID, sizeof(selfID));
  this->myPlayerID = selfID;

  return true;
}

int Client::run(std::string& host, std::string& port, uint32_t lobbyID, std::string& mapFile){

  this->connectToServer(host, port);

  if(!this->joinMatch(lobbyID)){
    return ERROR;
  }

  SdlWindow window(WIDTH, HEIGHT);
  ClientMapLoader loader(mapFile, 24, 24);
  Map matrix(loader);

  TextureManager manager(&window);
  manager.loadTextures();
  AudioManager audios;

  std::mutex m;

  std::atomic<bool> alive;
  alive = true;
  Player* player = new Player(3.0, 3.0, -1.0, 0.0, 0.0, 0.66, 0);
  Hud hud(&window, player, manager, audios);
  std::map<uint32_t,Player*> players;
  players[this->myPlayerID] = player;

  std::cout << "[CLIENT] Player Succesfully connected with ID: " << myPlayerID << std::endl;

  std::vector<Drawable*> sprites = loader.getDrawableItemList(); // Falta tener bien los ids de los sprites.

  Raycaster caster(manager, matrix, alive, &window, player, sprites, m, hud);
  int exitcode = 0;
  CommandSender* sender = new CommandSender(socket, alive);
  //LuaSender* sender = new LuaSender(socket, alive);
  CommandExecuter* worker = new CommandExecuter(socket, alive, sprites, players, m, myPlayerID, audios, matrix, loader);

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
