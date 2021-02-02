#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "sdlwindow.h"
#include <atomic>
#include <vector>

class ScoreBoard {
 private:
  SdlWindow* window;
  std::vector<uint32_t> ids;
  std::vector<uint32_t> scores;
 public:
  ScoreBoard(SdlWindow* window): window(window), end(false) {}
  bool end;
  void pushId(uint32_t value);
  void pushScore(uint32_t value);
  void draw();
};

#endif  // SCOREBOARD_H_
