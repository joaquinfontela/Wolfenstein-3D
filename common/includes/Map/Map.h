#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <cstring>
#include <string>

#include "../../../client/includes/ClientMapLoader.h"
#include "../../../client/includes/clientprotocol.h"
#include "../../../client/includes/doortile.h"

/**
 * @brief [CLIENT SIDE] Knows where are all the doors and walls.
 *
 */
class Map {
 public:
  DoorTile* doors;
  int* matrix;
  int dimx;
  int dimy;

  /**
   * @brief [CLIENT SIDE] Construct a new Map object
   *
   * @param loader
   */
  Map(ClientMapLoader& loader);

  /**
   * @brief [CLIENT SIDE] Destroy the Map object and deallocates the matrix and
   * door pointers.
   *
   */
  ~Map();

  /**
   * @brief [CLIENT SIDE] Get the doortile timer attribute.
   *
   * @param x Door X Coordinate.
   * @param y Door Y Coordinate.
   * @return float Doortile's timer.
   */
  float getTimers(int x, int y);

  /**
   * @brief [CLIENT SIDE] Updates all timers with a new value.
   *
   * @param value Time update.
   */
  void updateTimers(float value);

  /**
   * @brief [CLIENT SIDE] Returns the matrix id from the given coordinates.
   *
   * @param x
   * @param y
   * @return int
   */
  int get(int x, int y);

  /**
   * @brief [CLIENT SIDE] Checks if coordinates are on a door.
   *
   * @param x
   * @param y
   * @return true
   * @return false
   */
  bool isDoor(int x, int y);

  /**
   * @brief [CLIENT SIDE] Get the Door's State.
   *
   * @param x
   * @param y
   * @return char
   */
  char getDoorState(int x, int y);

  /**
   * @brief [CLIENT SIDE] Calls the method changeState() on the given door.
   *
   * @param x
   * @param y
   * @return True if its a fake wall, false otherwise.
   */
  bool switchDoorState(int x, int y);

  /**
   * @brief [CLIENT SIDE] If the given door is closed it switches to open and
   * the other way around.
   *
   * @param x
   * @param y
   */
  void forceDoorState(int x, int y);

  /**
   * @brief [CLIENT SIDE] Get the Matrix.
   *
   * @return int* Pointer to the first value of the dynamic matrix.
   */
  int* getMatrix();

  /**
   * @brief [CLIENT SIDE] Returns the sound code for the given door coordinates.
   *
   * @param x Door X Coord.
   * @param y Door Y Coord.
   * @return Sound code.
   */
  int getDoorSound(int x, int y);
};

#endif  // TP_FINAL_MAP_H
