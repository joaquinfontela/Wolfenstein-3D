#include "../../../includes/Control/Command/StartGame.h"
#include "../../../includes/Control/Notification/Notification.h"


StartGame::StartGame(int ID) {
  this->playerID = ID;

}

void StartGame::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  if(!game.hasStarted())
    game.start(this->playerID, notifications);
}
