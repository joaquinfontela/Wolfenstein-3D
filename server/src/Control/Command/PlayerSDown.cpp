#include "../../../includes/Control/Command/PlayerSDown.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerSDown::PlayerSDown(int ID) {
  this->playerID = ID;

}

void PlayerSDown::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  double moveSpeed = -0.25;
  game.updatePlayerMoveSpeed(this->playerID, moveSpeed);
}
