#ifndef __CHANGE_DOOR_STATUS_H__
#define __CHANGE_DOOR_STATUS_H__

#include "Updatable.h"

/**
	* @section DESCRIPTION 
  * Class that represents an event that needs to be updated in time.
	*
  */

class ChangeDoorStatus : public Updatable{

private:
  float timeRequired;
  bool requiresNotification;
  int x, y;

public:
  ChangeDoorStatus(int x, int y, float timeRequired, bool requiresNotification);
  
/**
	* <Updates the event through time>
	*
	* @param Time elapsed in seconds since last update.
	* @param The game on which to update the event.
  * @param The notification Queue on which to notify of change if needed.
  *
  */
  void update(float timeElapsed, Game& game, WaitingQueue<Notification*>& notif);

  /**
	* <Notifies of the event status and change>
	*
	* @param The notification queue on which to notify.
	*
  * @return Boolean indicating if the event is finished or not.
  */
  bool notify(WaitingQueue<Notification*>& notif);

};




#endif
