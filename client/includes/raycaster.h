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
#include "drawablevector.h"
#include "hud.h"
#include "player.h"
#include "startingscreen.h"
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
   * @param player Reference to one's own player.
   * @param sprites Sprites vector.
   * @param hud Reference to the hud.
   */
  Raycaster(TextureManager& manager, Map& m, std::atomic<bool>& b,
            Player* player, DrawableVector& sprites, Hud& hud,
            StartingScreen& startingscreen)
      : alive(b),
        manager(manager),
        matrix(m),
        player(player),
        sprites(sprites),
        hud(hud),
        startingscreen(startingscreen) {
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
  StartingScreen& startingscreen;
  std::atomic<bool>& alive;
  TextureManager& manager;
  Map& matrix;
  Player* player;
  DrawableVector& sprites;
  Hud& hud;
  int width, height;
  std::vector<Door> doors;
  double dirX, dirY, x, y, planeX, planeY;

  /**
   * @brief Sleeps the engine thread to cap the fps on 60.
   *
   */
  void sleep(float diff);

  /**
   * @brief Takes coordinate-like information from the player.
   *
   */
  void getPlayerData();

  /**
   * @brief Raycasts the game walls and objects iterating through every pixel column.
   *
   */
  void rayCastGame(double* distanceBuffer);

  /**
   * @brief Permorms the DDA algorithm with the given data, to calculate wall and door hits.
   *
   */
  void DDA(int& side, int& texNum, int& i, int& dx, int& dy, int& matrixXCoord,
          int& matrixYCoord, double& sideDistX, double& sideDistY,
          double& deltaDistanceX, double& deltaDistanceY, double& cameraXCoord);

  /**
   * @brief Draws doors and pops them out of their vector.
   *
   */
   void drawDoors(double* distanceBuffer);

   /**
    * @brief Draws walls from the DDA generated data.
    *
    */
   void drawWalls(int& side, int& texNum, int& i, int& dx, int& dy,
                double* distanceBuffer, int& matrixXCoord, int& matrixYCoord,
                double rayDirX, double rayDirY);
};

#endif  // RAYCASTER_H_
