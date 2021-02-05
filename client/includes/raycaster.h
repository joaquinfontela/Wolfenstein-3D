#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include <math.h>

#include <atomic>
#include <iostream>
#include <mutex>
#include <vector>

#include "../../common/includes/Map/Map.h"
#include "clientprotocol.h"
#include "door.h"
#include "hud.h"
#include "player.h"
#include "scoreboard.h"
#include "sdlwindow.h"
#include "texturemanager.h"

#define MAX_NUMBER_OF_DOORS_PER_FRAME 10

/**
 * @brief Game engine. Draws the game using the raycasting algorithm.
 *
 */
class Raycaster {
 public:
  /**
   * @brief Construct a new Raycaster object
   *
   * @param manager Reference to the texture manager.
   * @param m Map reference.
   * @param b Boolean that represents if the game has finished or not.
   * @param window Window reference.
   * @param player Reference to one's own player.
   * @param sprites Sprites vector.
   * @param lock Stops from accesing a deleted sprite.
   * @param hud Reference to the hud.
   * @param scoreboard Reference to the scoreboard.
   */
  Raycaster(TextureManager& manager, Map& m, std::atomic<bool>& b,
            SdlWindow* window, Player* player, std::vector<Drawable*>& sprites,
            std::mutex& lock, Hud& hud, ScoreBoard& scoreboard)
      : alive(b),
        manager(manager),
        matrix(m),
        player(player),
        window(window),
        sprites(sprites),
        lock(lock),
        hud(hud),
        scoreboard(scoreboard) {
    manager.getWindowSize(&this->width, &this->height);
    this->doors.reserve(MAX_NUMBER_OF_DOORS_PER_FRAME);
  }

  /**
   * @brief Verifies if the given coordinates are from a door.
   *
   * @param matrixXCoord
   * @param matrixYCoord
   * @return true
   * @return false
   */
  bool hitDoor(const int& matrixXCoord, const int& matrixYCoord);

  /**
   * @brief Runs the game engine. Draws the environment and updates the time for
   * all the objects that need it.
   *
   */
  void run();

 private:
  Area destArea;
  Area srcArea;
  std::atomic<bool>& alive;
  TextureManager& manager;
  Map& matrix;
  Player* player;
  SdlWindow* window;
  std::vector<Drawable*>& sprites;
  std::mutex& lock;
  Hud& hud;
  int width, height;
  std::vector<Door> doors;
  ScoreBoard& scoreboard;
};

#endif  // RAYCASTER_H_
