#include "doortile.h"

#include "clientprotocol.h"

void DoorTile::updateTimer(float update) {
  if (state == OPEN || state == CLOSED) return;
  if (state == OPENING) {
    this->timer -= update;
    if (this->timer <= 0) {
      this->timer = 0;
      state = OPEN;
    }
  } else if (state == CLOSING) {
    this->timer += update;
    if (this->timer >= DOOR_ANIMATION_TIME) {
      this->timer = DOOR_ANIMATION_TIME;
      state = CLOSED;
    }
  }
}

void DoorTile::changeState() {
  if (state == OPEN || state == OPENING)
    state = CLOSING;
  else if (state == CLOSED || state == CLOSING)
    state = OPENING;
}
