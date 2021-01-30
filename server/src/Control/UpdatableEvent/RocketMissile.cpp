#include "../../../includes/Control/UpdatableEvent/RocketMissile.h"
#include "../../../includes/Control/Notification/MissileExplotion.h"
#include "../../../includes/Control/Notification/ElementSwitchPosition.h"


RocketMissile::RocketMissile(double x, double y, double dirX, double dirY, int uniqueId, double planeX, double planeY) : Updatable(), x(x), y(y), dirX(dirX), dirY(dirY), uniqueId(uniqueId){
    this->xDisplacement = planeX;
    this->yDisplacement = planeY;
}

void RocketMissile::update(float timeElapsed, Game& game, WaitingQueue<Notification*>& notif){
  double newX = x + dirX * (moveSpeed * (timeElapsed));
  double newY = y + dirY * (moveSpeed * (timeElapsed));
  this->hasToBeNotified = true;


  double quarterStepX = (newX - x) / 4;
  double quarterStepY = (newY - y) / 4;

  int i = 0;
  while(i < 4){
    if(!(this->done = game.moveRocketMissileFrom(this->x, this->y, x + quarterStepX, y + quarterStepY, notif))){
      x = x + quarterStepX;
      y = y + quarterStepY;
      i++;
    }else
      break;
  }
}

bool RocketMissile::notify(WaitingQueue<Notification*>& notif){

  if(this->hasToBeNotified){
    ElementSwitchPosition* posUpdate = new ElementSwitchPosition(this->uniqueId, this->x + xDisplacement, this->y + yDisplacement);
    notif.push(posUpdate);

    if(this->done){
      MissileExplotion* noti = new MissileExplotion(this->uniqueId);
      notif.push(noti);
      return true;
    }
  }


  return false;
}
