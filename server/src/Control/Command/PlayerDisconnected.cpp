#include "../../../includes/Control/Command/PlayerDisconnected.h"

#include <map>

#include "../../../includes/Control/Notification/Notification.h"
#include "../../../includes/Control/Notification/PlayerDisconnect.h"

PlayerDisconnected::PlayerDisconnected(int ID) {
  this->playerID = ID;

}

void PlayerDisconnected::execute(WaitingQueue<Notification*>& notifications, Game& game) {

  if(game.removePlayer(this->playerID)){
    PlayerDisconnect* noti = new PlayerDisconnect(this->playerID);
    notifications.push(noti);
  }

}
