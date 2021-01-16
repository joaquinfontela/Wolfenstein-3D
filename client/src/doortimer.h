#ifndef DOORTIMER_H_
#define DOORTIMER_H_

#include <atomic>
#include "../../common/includes/Map/Map.h"
#include "../../common/includes/Thread/Thread.h"

// We need this to run in another thread so that
// we can measure time without any delays that could
// arise, for example, from raycasting.

class DoorTimer : public Thread {
 public:
  DoorTimer(Map& matrix, std::atomic<bool>& alive) : matrix(matrix), alive(alive) {}
  void run();
 private:
  Map& matrix;
  std::atomic<bool>& alive;
};

#endif  // DOORTIMER_H_
