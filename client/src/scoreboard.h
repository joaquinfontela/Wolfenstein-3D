#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include <atomic>
#include <mutex>
#include <tuple>
#include <vector>

#include "sdlwindow.h"

class ScoreBoard {
 private:
  SdlWindow* window;
  std::vector<std::tuple<uint32_t, uint32_t>> scores;
  std::vector<std::tuple<uint32_t, uint32_t>> kills;
  std::vector<std::tuple<uint32_t, uint32_t>> shotsfired;
  bool end;
  std::mutex m;

  /**
   * @brief Renders the top scores from the leaderboards.
   *
   * @param width Screen width in pixels.
   * @param height Screen height in pixels.
   */
  void renderScore(int width, int height);

  /**
   * @brief Renders the top killers from the leaderboards.
   *
   * @param width Screen width in pixels.
   * @param height Screen height in pixels.
   */
  void renderKills(int width, int height);

  /**
   * @brief Renders the top shooters from the leaderboards.
   *
   * @param width Screen width in pixels.
   * @param height Screen height in pixels.
   */
  void renderShotsFired(int width, int height);

  /**
   * @brief Renders text aligned to look well for the leaderboards.
   *
   * @param text Text to render.
   * @param row Row of text to render.
   * @param column Column of text to render.
   * @param w Screen width in pixels.
   * @param h Screen height in pixels.
   */
  void renderText(const char* text, int row, int column, int w, int h);

 public:
  /**
   * @brief Tells if the leaderboard is being drawn.
   *
   * @return true if it's being drawn.
   * @return false if it's finished.
   */
  bool hasEnded();

  /**
   * @brief Stop drawing the leaderboard screen.
   *
   */
  void stop();
  ScoreBoard(SdlWindow* window) : window(window), end(false) {}

  /**
   * @brief Pushes the value sent from the server to be drawn on the
   * leaderboards
   *
   * @param value It's a <id, score> tuple
   */
  void pushScore(std::tuple<uint32_t, uint32_t> value);

  /**
   * @brief Pushes the value sent from the server to be drawn on the
   * leaderboards
   *
   * @param value It's a <id, kills> tuple
   */
  void pushKills(std::tuple<uint32_t, uint32_t> value);

  /**
   * @brief Pushes the value sent from the server to be drawn on the
   * leaderboards
   *
   * @param value It's a <id, shots fired> tuple
   */
  void pushShotsfired(std::tuple<uint32_t, uint32_t> value);

  /**
   * @brief Draws the leaderboard by calling the other methods.
   *
   */
  void draw();
};

#endif  // SCOREBOARD_H_
