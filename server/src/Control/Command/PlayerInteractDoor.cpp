#include "../../../includes/Control/Command/PlayerInteractDoor.h"

#include <map>
#include <functional>

#include "../../../includes/Control/Notification/Notification.h"
#include "../../../includes/Control/Notification/DoorMoving.h"

PlayerInteractDoor::PlayerInteractDoor(int ID) {
  this->playerID = ID;

}

void PlayerInteractDoor::execute(WaitingQueue<Notification*>& notifications, Game& game) {

  if(!game.hasStarted())
    return;

  int x, y;

  std::tie(x, y) = game.moveDoor(this->playerID);  // Las coordenadas (x, y) de la puerta con la que se interactuo, si no habia ninguna tendria (-1, -1)


  if(x < 0 || y < 0)
    return;

  DoorMoving* noti = new DoorMoving(x, y);
  notifications.push(noti);

}
