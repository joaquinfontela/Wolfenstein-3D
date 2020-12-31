#include "../../../includes/Control/Command/PlayerAUp.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerAUp::PlayerAUp(int ID) {
  this->playerID = ID;

}

void PlayerAUp::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  double rotSpeed = -0.125;
  game.updatePlayerRotationSpeed(this->playerID, rotSpeed);
}
