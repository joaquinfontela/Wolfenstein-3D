#include "../../../includes/Control/Command/PlayerDDown.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerDDown::PlayerDDown(int ID) {
  this->playerID = ID;

}

void PlayerDDown::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  if(!game.hasStarted())
    return;

  double rotSpeed = -0.1;
  game.updatePlayerRotationSpeed(this->playerID, rotSpeed);
}
