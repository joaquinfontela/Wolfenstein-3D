#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include <atomic>
#include <mutex>
#include <tuple>
#include <vector>

#include "texturemanager.h"

/**
 * @brief Stores the data for the leaderboards and draws it.
 *
 */
class ScoreBoard {
 private:
  std::vector<std::tuple<uint32_t, uint32_t>> scores;
  std::vector<std::tuple<uint32_t, uint32_t>> kills;
  std::vector<std::tuple<uint32_t, uint32_t>> shotsfired;
  bool end;
  TextureManager& manager;
  std::mutex m;

  /**
   * @brief Renders the top scores from the leaderboards.
   *
   * @param width Screen width in pixels.
   * @param height Screen height in pixels.
   * @param rows Row to render to.
   * @param list <id, score> Tuple vector.
   */
  void renderScores(int width, int height, int col,
     std::vector<std::tuple<uint32_t, uint32_t>>& list);

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

  /**
   * @brief Similar to renderText but with some values shifted to
   * better render the title of each column.
   *
   */
  void renderTitle(const char* text, int row, int column, int w, int h);

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
  ScoreBoard(TextureManager& manager) : end(false) , manager(manager) {}

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
