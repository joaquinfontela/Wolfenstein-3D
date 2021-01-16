#ifndef DOORTILE_H_
#define DOORTILE_H_

#include "clientprotocol.h"

class DoorTile {
 private:
  float timer;
 public:
  char state;
  bool isDoor;
  void setDoor(bool isDoor);
  void changeState();
  DoorTile() : isDoor(false), state(CLOSED), timer(0) {}
  void updateTimer(float update);
};

#endif  // DOORTILE_H_
