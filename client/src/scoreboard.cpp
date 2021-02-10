#include "../includes/scoreboard.h"
#include "../includes/texturemanager.h"
#include "../includes/clientprotocol.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <mutex>
#include <string>
#include <tuple>

void ScoreBoard::renderText(const char* text, int rows, int column, int w,
                            int h) {
  SDL_Rect rect = {.x = w / 15 + column * (2 * w / 15 + w / 5),
                   .y = (h * rows) / 6,
                   .w = w / 5,
                   .h = h >> 3};
  this->manager.renderText(text, &rect);
}

void ScoreBoard::renderTitle(const char* text, int rows, int column, int w,
                            int h) {
  int imgw = 9 * w / 50;
  SDL_Rect rect = {.x = 27 * w * (column + 1)/ 250 + imgw * column,
                   .y = 10 * (h * rows) / 50,
                   .w = imgw,
                   .h = h >> 3};
  this->manager.renderText(text, &rect);
}

void ScoreBoard::renderScores(int width, int height, int col,
                         std::vector<std::tuple<uint32_t, uint32_t>>& list) {
  int rows = list.size();
  for (int i = 0; i < rows; i++) {
    std::tuple<uint32_t, uint32_t> score = list[i];
    std::string val = "Player " +
                      std::to_string(std::get<0>(score)) +
                      ": " + std::to_string(std::get<1>(score));
    this->renderText(val.c_str(), i + 2, col, width, height);
  }
}

void ScoreBoard::draw() {
  int height, width;
  SDL_Rect rect;
  while (!this->hasEnded()) {
    this->manager.getWindowSize(&width, &height);
    this->manager.renderComplete(HIGHSCORE);
    rect = {.x = (3 * width) >> 3,
            .y = -(height >> 2) / 6,
            .w = width >> 2,
            .h = height >> 2};
    this->renderScores(width, height, 0, scores);
    this->renderScores(width, height, 1, shotsfired);
    this->renderScores(width, height, 2, kills);
    this->manager.updateScreen();
  }
}

void ScoreBoard::pushScore(std::tuple<uint32_t, uint32_t> value) {
  this->scores.push_back(value);
}

void ScoreBoard::pushKills(std::tuple<uint32_t, uint32_t> value) {
  this->kills.push_back(value);
}

void ScoreBoard::pushShotsfired(std::tuple<uint32_t, uint32_t> value) {
  this->shotsfired.push_back(value);
}

bool ScoreBoard::hasEnded() {
  std::unique_lock<std::mutex> lock(this->m);
  return this->end;
}

void ScoreBoard::stop() {
  std::unique_lock<std::mutex> lock(this->m);
  this->end = true;
}
