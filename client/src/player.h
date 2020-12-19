#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdint>

class Player {
 private:
  uint32_t x;
  uint32_t y;
  uint32_t viewAngle;
 public:
  int getX();
  int getY();
  int getAngle();
  Player() : x(370), y(370), viewAngle(0) {}
  void goTo(uint32_t x, uint32_t y, uint32_t angle);
};

#endif  // PLAYER_H_
