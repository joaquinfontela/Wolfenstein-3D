#include "../../../includes/Control/Command/PlayerDDown.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerDDown::PlayerDDown(int ID) {
  this->playerID = ID;

}

void PlayerDDown::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  double rotSpeed = -0.125;
  game.updatePlayerRotationSpeed(this->playerID, rotSpeed);
}
