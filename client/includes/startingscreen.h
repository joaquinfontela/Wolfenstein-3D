#ifndef STARTINGSCREEN_H_
#define STARTINGSCREEN_H_

#include "texturemanager.h"

class StartingScreen {
 private:
  TextureManager& manager;
  bool drawing;
 public:
  StartingScreen(TextureManager& manager) : manager(manager), drawing(true) {}
  void draw();
  void stop();
};

#endif  // STARTINGSCREEN_H_
