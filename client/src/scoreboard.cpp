#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "scoreboard.h"

void ScoreBoard::draw() {
  int height, witdh;
  this->window->getWindowSize(&witdh, &height);
  SDL_Rect rect = {.x = 0, .y = 0, .w = witdh/2, .h = height/2};
  this->window->fill();
  this->window->renderText("buenas tardes", &rect);
  this->window->render();
}

void ScoreBoard::pushId(uint32_t value) {
  this->ids.push_back(value);
}
void ScoreBoard::pushScore(uint32_t value) {
  this->scores.push_back(value);
}
