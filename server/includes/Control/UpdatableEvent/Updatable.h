#ifndef __UPDATABLE_H__
#define __UPDATABLE_H__

#include "../../Model/Game/Game.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../Notification/Notification.h"

class Game;

/**
  * @section DESCRIPTION
  * The class that represents a time limited event.
*/
class Updatable{

protected:

  float timeElapsed;
  bool hasToBeNotified;
  bool done;

public:

  Updatable() : timeElapsed(0.0f), hasToBeNotified(false), done(false){}

  /**
    * <Updates the event given the elapsed time>
    *
    * @param Time elapsed since the last update.
    * @param The game in which the event is occuring.
    * @param The queue in which notifications are placed.
  */
  virtual void update(float timeElapsed, Game& game, WaitingQueue<Notification*>& notif) = 0;

  /**
    * <Notifies if needed the change of status of the event>
    *
    * @param The notification queue to place the notification.
    * @return Boolean representing if the event has finished.
  */
  virtual bool notify(WaitingQueue<Notification*>& notif) = 0;
  ~Updatable(){}

};


#endif
