#ifndef __CHANGE_DOOR_STATUS_H__
#define __CHANGE_DOOR_STATUS_H__

#include "Updatable.h"


class ChangeDoorStatus : public Updatable{

private:
  float timeRequired;
  int x, y;

public:
  ChangeDoorStatus(int x, int y);
  void update(float timeElapsed, Game& game);
  bool notify(WaitingQueue<Notification*>& notif);

};




#endif
