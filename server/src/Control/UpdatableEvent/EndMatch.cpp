#include "../../../includes/Control/UpdatableEvent/EndMatch.h"

#include <iostream>

EndMatch::EndMatch(float timeRequired) : Updatable(), timeRequired(timeRequired) {}

void EndMatch::update(float timeElapsed, Game& game,
                      WaitingQueue<Notification*>& notif) {
  this->timeElapsed += timeElapsed;

  if (this->timeElapsed > this->timeRequired && !done) {
    if (game.hasStarted()) game.end(notif);

    std::cout << "[GAME] Ending Match..." << std::endl;
    done = true;
  }
}

bool EndMatch::notify(WaitingQueue<Notification*>& notif) {
  // Create a game end noti.
  return done;
}
