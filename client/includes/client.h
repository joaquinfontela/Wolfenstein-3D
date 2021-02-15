#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <SDL2/SDL.h>

#include <atomic>
#include <chrono>
#include <exception>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "../../common/includes/Map/Map.h"
#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/protocol.h"
#include "ClientMapLoader.h"
#include "audiomanager.h"
#include "clientprotocol.h"
#include "commandexecuter.h"
#include "commandsender.h"
#include "hud.h"
#include "player.h"
#include "raycaster.h"
#include "sdlwindow.h"
#include "texturemanager.h"

/**
 * @brief Connects to the server and calls the game object.
 *
 */
class Client {
 private:
  SocketCommunication& socket;
  uint32_t myPlayerID = -1;
  SdlWindow* window;


  /**
   * @brief Connects to the game server.
   *
   * @param host
   * @param port
   */
  void connectToServer(std::string& host, std::string& port);

  /**
   * @brief Creates the window, and sets is to fullscreen if needed.
   *
   */
  void buildWindow();

 public:
  ~Client();
  Client(SocketCommunication& socket, int myPlayerID);

  /**
   * @brief Starts the game object.
   *
   */
  int run(std::string& mapFile);
};

#endif
