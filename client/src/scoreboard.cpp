#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "scoreboard.h"

void ScoreBoard::draw() {
  int height, witdh;
  this->manager.getWindowSize(&witdh, &height);
  SDL_Rect rect = {.x = 0, .y = 0, .w = witdh, .h = height};
  this->manager.accessWindow()->fill();
  this->manager.renderText("buenas tardes", &rect);
}

void ScoreBoard::pushId(uint32_t value) {
  this->ids.push_back(value);
}
void ScoreBoard::pushScore(uint32_t value) {
  this->scores.push_back(value);
}
