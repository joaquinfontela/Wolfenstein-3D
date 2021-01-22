#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <string>
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
#include "luasender.h"

class Client{
 private:
  SocketCommunication socket;
  uint32_t myPlayerID = -1;

  bool joinMatch(uint32_t lobbyID);
  void connectToServer(std::string& host, std::string& port);


 public:
  Client() : socket(-1){}
  int run(std::string& host, std::string& port, uint32_t lobbyID, std::string& mapFile);

};


#endif
