#include "scoreboard.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <mutex>
#include <string>
#include <tuple>

#define BLUE 0, 0, 176, 0

void ScoreBoard::renderText(const char* text, int rows, int column, int w,
                            int h) {
  SDL_Rect rect = {.x = 5 * w / 48 + column * 15 * w / 48,
                   .y = (h * rows) / 6,
                   .w = w >> 3,
                   .h = h >> 3};
  this->window->renderText(text, &rect);
}

void ScoreBoard::draw() {
  std::string scores = "Scores";
  std::string kills = "Kills";
  std::string shotsfired = "Shots Fired";
  int rows = this->scores.size();
  int height, width;
  SDL_Rect rect;
  while (!this->hasEnded()) {
    this->window->getWindowSize(&width, &height);
    rect = {.x = (3 * width) >> 3,
            .y = -(height >> 2) / 5,
            .w = width >> 2,
            .h = height >> 2};
    this->window->fill(BLUE);
    this->window->renderText("Leaderboards", &rect);
    rect = {.x = 0, .y = height >> 2, .w = width / 3, .h = rows * height >> 2};
    this->renderText(scores.c_str(), 1, 0, width, height);
    this->renderText(kills.c_str(), 1, 1, width, height);
    this->renderText(shotsfired.c_str(), 1, 2, width, height);

    for (int i = 0; i < rows; i++) {
      std::tuple<uint32_t, uint32_t> score = this->scores[i];
      std::string val = std::to_string(i + 1) + ")  Id(" +
                        std::to_string(std::get<0>(score)) +
                        "): " + std::to_string(std::get<1>(score));
      this->renderText(val.c_str(), i + 2, 0, width, height);
    }

    for (int i = 0; i < rows; i++) {
      std::tuple<uint32_t, uint32_t> score = this->kills[i];
      std::string val = std::to_string(i + 1) + ")  Id(" +
                        std::to_string(std::get<0>(score)) +
                        "): " + std::to_string(std::get<1>(score));
      this->renderText(val.c_str(), i + 2, 1, width, height);
    }
    /*
        for (int i = 0; i < rows; i++) {
          std::tuple<uint32_t, uint32_t> score = this->shotsfired[i];
          std::string val = std::to_string(i+1) + ")  Id(" +
       std::to_string(std::get<0>(score))
                            + "): " + std::to_string(std::get<1>(score));
          this->renderText(val.c_str(), i+2, 2, width, height);
        }
    */
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
