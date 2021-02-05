#ifndef DOORTIMER_H_
#define DOORTIMER_H_

#include <atomic>

#include "../../common/includes/Map/Map.h"
#include "../../common/includes/Thread/Thread.h"

/**
 * @brief Updates map timers. We need this to run in another thread so that we
 * can measure time without any delays that could arise, for example, from
 * raycasting.
 */
class DoorTimer : public Thread {
 public:
  /**
   * @brief Construct a new Door Timer object
   *
   * @param matrix
   * @param alive
   */
  DoorTimer(Map& matrix, std::atomic<bool>& alive)
      : matrix(matrix), alive(alive) {}

  /**
   * @brief Updates the map timers.
   *
   */
  void run();

 private:
  /**
   * @brief Map reference.
   *
   */
  Map& matrix;

  /**
   * @brief Will be set to false once the game ends.
   *
   */
  std::atomic<bool>& alive;
};

#endif  // DOORTIMER_H_
