#ifndef __END_MATCH_H__
#define __END_MATCH_H__

#include "Updatable.h"


class EndMatch : public Updatable{

private:
  float timeRequired;


public:
  EndMatch(float timeRequired);
  void update(float timeElapsed, Game& game, WaitingQueue<Notification*>& notif);
  bool notify(WaitingQueue<Notification*>& notif);

};




#endif
