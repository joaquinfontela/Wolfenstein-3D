#ifndef __LUA_CLIENT_H__
#define __LUA_CLIENT_H__
#include <atomic>
#include <chrono>
#include <exception>
#include <iostream>
#include <mutex>
#include <thread>

#include "../../../common/includes/Map/Map.h"
#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../../../common/includes/protocol.h"
#include "../includes/ClientMapLoader.h"
#include "../includes/clientprotocol.h"
#include "../includes/drawable.h"
#include "../includes/log.h"
#include "../includes/player.h"
#include "../includes/texturemanager.h"
#include "luasender.h"

namespace Lua {

class Client {
 private:
  SocketCommunication socket;
  uint32_t myPlayerID = -1;
  uint32_t mapID = -1;

  void receiveAvailableMatch();
  bool joinMatch(uint32_t lobbyID);
  void connectToServer(std::string& host, std::string& port);

 public:
  Client() : socket() {}
  int run(std::string& host, std::string& port, uint32_t lobbyID, std::string& scriptName);
};
}  // namespace Lua

#endif
