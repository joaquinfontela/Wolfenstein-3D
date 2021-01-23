#include "../../../includes/Control/Command/PlayerMove.h"

#include <list>

#include "../../../includes/Control/Notification/Notification.h"
#include "../../../includes/Control/Notification/PlayerUpdatePosition.h"

PlayerMove::PlayerMove(int ID, int x, int y) {
  this->playerID = ID;
  this->x = x;
  this->y = y;
}

void PlayerMove::execute(WaitingQueue<Notification*>& notifications, Game& game) {

  if(!game.hasStarted())
    return;
    
  // Aca se usaria la clase Game para validar movimientos y en caso de tener que informar algo hacerlo.
  // La notificacion no deberia enviarse siempre, solo en el caso de que el movimiento que estoy intentando hacer sea valido.
  PlayerUpdatePosition* noti =
      new PlayerUpdatePosition(this->playerID, this->x, this->y);
  notifications.push(noti);
}
