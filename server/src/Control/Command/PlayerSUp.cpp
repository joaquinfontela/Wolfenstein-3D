#include "../../../includes/Control/Command/PlayerSUp.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerSUp::PlayerSUp(int ID) {
  this->playerID = ID;

}

void PlayerSUp::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  double movSpeed = 6.5;
  game.updatePlayerMoveSpeed(this->playerID, movSpeed);
}
