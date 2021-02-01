#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "texturemanager.h"
#include <atomic>

class ScoreBoard {
 private:
  TextureManager& manager;
 public:
  ScoreBoard(TextureManager& manager): manager(manager) {}
  void draw();
};

#endif  // SCOREBOARD_H_
