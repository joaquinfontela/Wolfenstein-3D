#ifndef DOOR_H
#define DOOR_H

class Door {
 public:
  Door() {}
  virtual bool isLocked() = 0;
  virtual bool unlock(bool hasKey) = 0;
  virtual bool lock() = 0;
  ~Door() {}
};

#endif
