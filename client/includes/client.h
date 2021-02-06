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
 * @brief Runs and coordinates all the main classes that execute the game.
 *
 */
class Client {
 private:
  SocketCommunication socket;
  uint32_t myPlayerID = -1;

  /**
   * @brief Gets a player id given a lobbyid.
   *
   * @param lobbyID
   * @return true if the operation is successful.
   * @return false if there is no connection.
   */
  bool joinMatch(uint32_t lobbyID);

  /**
   * @brief Connects to the game server.
   *
   * @param host
   * @param port
   */
  void connectToServer(std::string& host, std::string& port);

  /**
   * @brief Deletes all the sprites dynamically allocated.
   *
   * @param sprites List of values to be deleted.
   */
  void gargabeCollector(std::vector<Drawable*>& sprites);

 public:
  Client() : socket(-1) {}

  /**
   * @brief Starts, runs and deletes all the objects involving the game. Creates
   * and deletes the window, map (and it's loader), audio and texture managers,
   * sprite list and raycaster engine, among others.
   *
   * @param host
   * @param port
   * @param lobbyID
   * @param mapFile Map yaml file name.
   * @return int -1 on error and 0 on success.
   */
  int run(std::string& host, std::string& port, uint32_t lobbyID,
          std::string& mapFile);
};

#endif
