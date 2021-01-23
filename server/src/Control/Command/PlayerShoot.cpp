#include "../../../includes/Control/Command/PlayerShoot.h"

#include "../../../includes/Control/Notification/Notification.h"
#include "../../../includes/Control/Notification/ShotsFired.h"

PlayerShoot::PlayerShoot(int ID, bool keyPressed) {
  this->keyPressed = keyPressed;
  this->playerID = ID;

}

void PlayerShoot::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  if(!game.hasStarted())
    return;
    
  game.setShooting(playerID, keyPressed);
}
