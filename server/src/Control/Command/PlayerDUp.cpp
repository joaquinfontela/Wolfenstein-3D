#include "../../../includes/Control/Command/PlayerDUp.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerDUp::PlayerDUp(int ID) {
  this->playerID = ID;

}

void PlayerDUp::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  if(!game.hasStarted())
    return;

  double rotSpeed = 0.1;
  game.updatePlayerRotationSpeed(this->playerID, rotSpeed);
}
