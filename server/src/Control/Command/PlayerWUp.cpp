#include "../../../includes/Control/Command/PlayerWUp.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerWUp::PlayerWUp(int ID) {
  this->playerID = ID;

}

void PlayerWUp::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  double movSpeed = -6.5;
  game.updatePlayerMoveSpeed(this->playerID, movSpeed);
}
