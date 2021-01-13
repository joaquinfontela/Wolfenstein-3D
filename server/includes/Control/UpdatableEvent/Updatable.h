#ifndef __UPDATABLE_H__
#define __UPDATABLE_H__

#include "../../Model/Game/Game.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../Notification/Notification.h"

class Game;

class Updatable{

protected:

  float timeElapsed;
  bool hasToBeNotified;
  bool done;

public:

  Updatable() : timeElapsed(0.0f), hasToBeNotified(false), done(false){}
  virtual void update(float timeElapsed, Game& game) = 0;
  virtual bool notify(WaitingQueue<Notification*>& notif) = 0;
  ~Updatable(){}

};


#endif
