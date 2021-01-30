#ifndef __LUA_CLIENT_H__
#define __LUA_CLIENT_H__
#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../../../common/includes/Map/Map.h"
#include "../../../common/includes/protocol.h"
#include "luasender.h"
#include "../clientprotocol.h"
#include "../ClientMapLoader.h"
#include "../player.h"
#include "../texturemanager.h"
#include "../drawable.h"
#include "../log.h"
#include <exception>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

namespace Lua{

  class Client{
   private:
    SocketCommunication socket;
    uint32_t myPlayerID = -1;

    bool joinMatch(uint32_t lobbyID);
    void connectToServer(std::string& host, std::string& port);


   public:
    Client() : socket(-1){}
    int run(std::string& host, std::string& port, uint32_t lobbyID, std::string& mapFile, std::string& scriptName);

  };
}



#endif
