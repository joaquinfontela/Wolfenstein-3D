#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "texturemanager.h"
#include <atomic>
#include <vector>

class ScoreBoard {
 private:
  TextureManager& manager;
  std::vector<uint32_t> ids;
  std::vector<uint32_t> scores;
 public:
  ScoreBoard(TextureManager& manager): manager(manager), end(false) {}
  bool end;
  void pushId(uint32_t value);
  void pushScore(uint32_t value);
  void draw();
};

#endif  // SCOREBOARD_H_
