#include "../../../includes/Control/Command/PlayerWDown.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerWDown::PlayerWDown(int ID) {
  this->playerID = ID;

}

void PlayerWDown::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  double moveSpeed = 0.25;
  game.updatePlayerMoveSpeed(this->playerID, moveSpeed);
}
