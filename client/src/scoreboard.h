#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "sdlwindow.h"
#include <atomic>
#include <vector>
#include <mutex>
#include <tuple>

class ScoreBoard {
 private:
  SdlWindow* window;
  std::vector<std::tuple<uint32_t, uint32_t>> scores;
  std::vector<std::tuple<uint32_t, uint32_t>> kills;
  std::vector<std::tuple<uint32_t, uint32_t>> shotsfired;
  bool end;
  std::mutex m;
  void renderText(const char* text, int row, int column, int w, int h);
 public:
  bool hasEnded();
  void stop();
  ScoreBoard(SdlWindow* window): window(window), end(false) {}
  void pushScore(std::tuple<uint32_t, uint32_t> value);
  void pushKills(std::tuple<uint32_t, uint32_t> value);
  void pushShotsfired(std::tuple<uint32_t, uint32_t> value);
  void draw();
};

#endif  // SCOREBOARD_H_
