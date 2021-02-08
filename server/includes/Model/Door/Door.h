#ifndef DOOR_H
#define DOOR_H

class Door {
 public:
  Door() {}

  /*
   * @return a boolean determining if its locked or not.
   */
  virtual bool isLocked() = 0;

  /*
   * @brief [SERVER-SIDE] Unlocks the door.
   *
   * @return a boolean determining if the door was unlocked by the execution of
   * the function or not (if it was already unlocked, it returns false).
   */
  virtual bool unlock(bool hasKey) = 0;

  /*
   * @brief [SERVER-SIDE] locks the door
   *
   * @return true
   */
  virtual bool lock() = 0;

  /*
   * @brief [SERVER-SIDE] Unlocks the door if locked, and sets opening to false;
   * otherwise it locks the door.
   */
  virtual void changeStatus() = 0;
  ~Door() {}
};

#endif
