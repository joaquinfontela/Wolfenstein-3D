#include "LuaClient.h"
#define MAX_NUMBER_OF_TEXTURES_PER_FRAME 100
#include "../log.h"
#include "GameState.h"
#include "luaexecuter.h"
#include "luaraycaster.h"
namespace Lua{

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
    Log::playerId = selfID;

    return true;
  }

  int Client::run(std::string& host, std::string& port, uint32_t lobbyID, std::string& mapFile, std::string& scriptName){

    this->connectToServer(host, port);

    if(!this->joinMatch(lobbyID)){
      return ERROR;
    }

    SdlWindow window(WIDTH, HEIGHT);
    ClientMapLoader loader(mapFile, 24, 24);
    Map matrix(loader);

    TextureManager manager(&window);
    manager.loadTextures();


    std::mutex m;
    std::atomic<bool> alive;
    alive = true;
    Player* player = new Player(3.0, 3.0, -1.0, 0.0, 0.0, 0.66, 0);

    std::map<uint32_t,Player*> players;
    players[this->myPlayerID] = player;

    std::vector<Drawable*> sprites = loader.getDrawableItemList();
    sprites.reserve(MAX_NUMBER_OF_TEXTURES_PER_FRAME);


    int exitcode = 0;

    double distanceBuffer[300] = {0};
    Lua::GameState gameState(matrix, player, distanceBuffer);
    LuaSender* sender = new LuaSender(socket, alive, scriptName, &gameState);
    Lua::CommandExecuter* worker = new Lua::CommandExecuter(this->socket, alive, sprites, players, m, myPlayerID, matrix, loader, gameState);
    Lua::Raycaster caster(matrix, alive, 300, 200, player, sprites, m, gameState, distanceBuffer);

    try {
      sender->start();
      worker->start();
      caster.run();
    } catch (std::exception& e) {
      LOG(e.what());
      exitcode = ERROR;
    }
    sender->join();
    worker->join();
    alive = false;

    delete player;
    delete worker;
    delete sender;
    return exitcode;

  }
}
