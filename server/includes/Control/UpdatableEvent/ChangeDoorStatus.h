#ifndef __CHANGE_DOOR_STATUS_H__
#define __CHANGE_DOOR_STATUS_H__

#include "Updatable.h"


class ChangeDoorStatus : public Updatable{

private:
  float timeRequired;
  bool requiresNotification;
  int x, y;

public:
  ChangeDoorStatus(int x, int y, float timeRequired, bool requiresNotification);
  void update(float timeElapsed, Game& game, WaitingQueue<Notification*>& notif);
  bool notify(WaitingQueue<Notification*>& notif);

};




#endif
