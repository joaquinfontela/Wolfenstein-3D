#include "../../../includes/Control/Command/PlayerAUp.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerAUp::PlayerAUp(int ID) {
  this->playerID = ID;

}

void PlayerAUp::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  if(!game.hasStarted())
    return;

  double rotSpeed = -0.1;
  game.updatePlayerRotationSpeed(this->playerID, rotSpeed);
}
