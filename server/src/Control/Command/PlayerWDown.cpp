#include "../../../includes/Control/Command/PlayerWDown.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerWDown::PlayerWDown(int ID) {
  this->playerID = ID;

}

void PlayerWDown::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  if(!game.hasStarted())
    return;
    
  double moveSpeed = 6.5;
  game.updatePlayerMoveSpeed(this->playerID, moveSpeed);
}
