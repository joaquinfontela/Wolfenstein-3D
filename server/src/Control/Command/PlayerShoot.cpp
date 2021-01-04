#include "../../../includes/Control/Command/PlayerShoot.h"

#include "../../../includes/Control/Notification/Notification.h"
#include "../../../includes/Control/Notification/ShotsFired.h"

PlayerShoot::PlayerShoot(int ID) {
  this->playerID = ID;

}

void PlayerShoot::execute(WaitingQueue<Notification*>& notifications, Game& game) {

  game.playerShoot(this->playerID);
  ShotsFired* noti = new ShotsFired(this->playerID);
  notifications.push(noti);
}
