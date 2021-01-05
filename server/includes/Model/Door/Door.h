#ifndef DOOR_H
#define DOOR_H

class Door {
 public:
  Door() {}
  virtual bool isLocked() = 0;
  ~Door() {}
};

#endif