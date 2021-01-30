#include "../../../includes/Control/UpdatableEvent/ChangeDoorStatus.h"
#include "../../../includes/Control/Notification/DoorMoving.h"


ChangeDoorStatus::ChangeDoorStatus(int x, int y, float timeRequired, bool requiresNotification) : Updatable(), timeRequired(timeRequired), x(x), y(y), requiresNotification(requiresNotification){}

void ChangeDoorStatus::update(float timeElapsed, Game& game, WaitingQueue<Notification*>& notif){

  this->timeElapsed += timeElapsed;

  if(this->timeElapsed > this->timeRequired && !done){
    if(game.forceDoorStatusChange(x, y)){
      this->hasToBeNotified = true;
      this->done = true;
    }
  }


}

bool ChangeDoorStatus::notify(WaitingQueue<Notification*>& notif){

  if(done && !this->requiresNotification)
    return true;

  if(!this->hasToBeNotified || !this->requiresNotification)
    return false;

  DoorMoving* noti = new DoorMoving(x, y);
  notif.push(noti);

  if(done)            // Si devuelve True, deberia eliminarse de la lista de Updatables.
    return true;

  return false;
}
