#include "../includes/scoreboard.h"
#include "../includes/sdltexture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <mutex>
#include <string>
#include <tuple>

void ScoreBoard::renderText(const char* text, int rows, int column, int w,
                            int h) {
  SDL_Rect rect = {.x = 5 * w / 48 + column * 15 * w / 48,
                   .y = (h * rows) / 6,
                   .w = w >> 3,
                   .h = h >> 3};
  this->window->renderText(text, &rect);
}

void ScoreBoard::renderTitle(const char* text, int rows, int column, int w,
                            int h) {
  int imgw = 9 * w / 50;
  SDL_Rect rect = {.x = 27 * w * (column + 1)/ 250 + imgw * column,
                   .y = 10 * (h * rows) / 50,
                   .w = imgw,
                   .h = h >> 3};
  this->window->renderText(text, &rect);
}

void ScoreBoard::renderScore(int width, int height) {
  int rows = this->scores.size();
  for (int i = 0; i < rows; i++) {
    std::tuple<uint32_t, uint32_t> score = this->scores[i];
    std::string val = std::to_string(i + 1) + ")  Id(" +
                      std::to_string(std::get<0>(score)) +
                      "): " + std::to_string(std::get<1>(score));
    this->renderText(val.c_str(), i + 2, 0, width, height);
  }
}

void ScoreBoard::renderKills(int width, int height) {
  int rows = this->kills.size();
  for (int i = 0; i < rows; i++) {
    std::tuple<uint32_t, uint32_t> score = this->kills[i];
    std::string val = std::to_string(i + 1) + ")  Id(" +
                      std::to_string(std::get<0>(score)) +
                      "): " + std::to_string(std::get<1>(score));
    this->renderText(val.c_str(), i + 2, 1, width, height);
  }
}

void ScoreBoard::renderShotsFired(int width, int height) {
  int rows = this->shotsfired.size();
  for (int i = 0; i < rows; i++) {
    std::tuple<uint32_t, uint32_t> score = this->shotsfired[i];
    std::string val = std::to_string(i + 1) + ")  Id(" +
                      std::to_string(std::get<0>(score)) +
                      "): " + std::to_string(std::get<1>(score));
    this->renderText(val.c_str(), i + 2, 2, width, height);
  }
}

void ScoreBoard::draw() {
  std::string scores = "Scores  ";
  std::string kills = "  Kills  ";
  std::string shotsfired = "Shots Fired";
  SdlTexture background("../media/highscores.png", *this->window);
  int height, width;
  SDL_Rect rect;
  while (!this->hasEnded()) {
    this->window->getWindowSize(&width, &height);
    background.renderAll({ .x = 0, .y = 0, .width = width, .height = height});
    rect = {.x = (3 * width) >> 3,
            .y = -(height >> 2) / 6,
            .w = width >> 2,
            .h = height >> 2};
    this->renderTitle(scores.c_str(), 1, 0, width, height);
    this->renderTitle(kills.c_str(), 1, 1, width, height);
    this->renderTitle(shotsfired.c_str(), 1, 2, width, height);
    this->renderScore(width, height);
    this->renderKills(width, height);
    this->renderShotsFired(width, height);
    this->window->render();
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
