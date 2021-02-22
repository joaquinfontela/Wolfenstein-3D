#include "../includes/startingscreen.h"
#include "../includes/texturemanager.h"
#include "../includes/clientprotocol.h"

#include <iostream>

void StartingScreen::stop() {
  this->drawing = false;
}

void StartingScreen::draw() {
  while (this->drawing) {
    this->manager.renderComplete(STARTING_SCREEN);
    this->manager.updateScreen();
  }
}
