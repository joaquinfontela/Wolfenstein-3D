#include "../../../includes/Control/Command/PlayerDUp.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerDUp::PlayerDUp(int ID) {
  this->playerID = ID;

}

void PlayerDUp::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  double rotSpeed = 0.125;
  game.updatePlayerRotationSpeed(this->playerID, rotSpeed);
}
