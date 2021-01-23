#include "../../../includes/Control/Command/PlayerSwitchWeapon.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerSwitchWeapon::PlayerSwitchWeapon(int playerID, int weaponPos) {
  this->playerID = playerID;
  this->weaponPos = weaponPos;

}

void PlayerSwitchWeapon::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  if(!game.hasStarted())
    return;
    
  game.playerSwitchWeapon(this->playerID, this->weaponPos);
}
