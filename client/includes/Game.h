#ifndef __GAME_H__
#define __GAME_H__
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
class Game{
private:
  uint32_t myPlayerID;
  SocketCommunication& socket;
  AudioManager audios;
  TextureManager manager;
  ScoreBoard scoreboard;
  StartingScreen starting;
  PlayerMap players;
  ClientMapLoader loader;

public:
  Game(SocketCommunication& socket, SdlWindow* window, uint32_t myPlayerID, std::string& mapFile);

  /**
   * @brief Starts, runs and deletes all the objects involving the game. Creates
   * and deletes the window, map (and it's loader), audio and texture managers,
   * sprite list and raycaster engine, among others.
   *
   */
  int start();
};

#endif
