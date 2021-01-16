#ifndef DOORTILE_H_
#define DOORTILE_H_

#include "clientprotocol.h"

class DoorTile {
 public:
  float timer;
  char state;
  bool isDoor;
  void setDoor(bool isDoor);
  void changeState();
  DoorTile() : isDoor(false), state(CLOSED), timer(1) {}
  void updateTimer(float update);
};

#endif  // DOORTILE_H_
