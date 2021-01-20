#ifndef __ROCKET_MISSILE_H__
#define __ROCKET_MISSILE_H__
#include "Updatable.h"

class RocketMissile : public Updatable{

private:
  int uniqueId;
  double dirX;
  double dirY;
  double x;
  double y;
  double moveSpeed = 20;

public:
  RocketMissile(double x, double y, double dirX, double dirY, int uniqueId);
  void update(float timeElapsed, Game& game);
  bool notify(WaitingQueue<Notification*>& notif);

};




#endif
