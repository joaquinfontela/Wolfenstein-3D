#ifndef DOORTILE_H_
#define DOORTILE_H_

#include "clientprotocol.h"

/**
 * @brief Represents a door state.
 *
 */
class DoorTile {
 public:
  /**
   * @brief Sets the doortile state to CLOSING if the door is OPEN or OPENING.
   * Sets the doortile state to OPENING if the door is CLOSED or CLOSING.
   *
   */
  void changeState();

  /**
   * @brief Updates the timer and door state if needed.
   *
   * @param update Time update.
   */
  void updateTimer(float update);

  DoorTile() : isDoor(false), state(CLOSED), timer(1) {}
  char state;
  bool isDoor;
  bool isFakeWall;

  /**
   * @brief Resets all values to initial state.
   *
   */
  void restart();

  /**
   * @brief Value that lies between 0 (fully opened) and 1 (fully closed).
   *
   */
  float timer;
};

#endif  // DOORTILE_H_
