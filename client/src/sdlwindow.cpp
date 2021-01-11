#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include "sdlexception.h"
#include "sdlwindow.h"
#include "sdltexture.h"
#include <iostream>
#include "clientprotocol.h"

#define SDL_INIT_ERROR "\nError on initialization: "
#define SDL_CEILING_INIT_ERROR "\nError on ceiling texture initialization "
#define SDL_WINDOW_INIT_ERROR "\nError on window initialization: "

SdlWindow::SdlWindow(int width, int height) :
                     width(width), height(height) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    throw SdlException(SDL_INIT_ERROR, SDL_GetError());
  }
  if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
      &this->window, &this->renderer)) {
    throw SdlException(SDL_WINDOW_INIT_ERROR, SDL_GetError());
  }
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
    throw SdlException(Mix_GetError());
  }
  if (!(ceilingPixel = new SdlTexture(IMG_PATH "ceiling.png", *this))) {
    throw SdlException(SDL_CEILING_INIT_ERROR, SDL_GetError());
  }
  SDL_SetWindowTitle(this->window, GAME_TITLE);
  SDL_Surface* icon = IMG_Load(IMG_PATH GAME_LOGO);
  SDL_SetWindowIcon(this->window,icon);
}

void SdlWindow::getWindowSize(int* w, int* h) {
  SDL_GetWindowSize(this->window, &this->width, &this->height);
  *w = this->width;
  *h = this->height;
}

void SdlWindow::killRenderer(){
  if (!this->renderer) return;
  SDL_DestroyRenderer(this->renderer);
  this->renderer = NULL;
}

void SdlWindow::killWindow(){
  if (!this->window) return;
  SDL_DestroyWindow(this->window);
  this->window = NULL;
}

void SdlWindow::killAudio() {
  Mix_CloseAudio();
  Mix_Quit();
}

SdlWindow::~SdlWindow() {
  delete this->ceilingPixel;
  this->killRenderer();
  this->killWindow();
  this->killAudio();
  SDL_Quit();
}

void SdlWindow::fillTransparent(int r, int g, int b) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, 1);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() { this->fill(0, 0, 0, 0); }

void SdlWindow::fillWolfenstein() {
  this->fill(FLOOR_COLOR, 0);
  this->ceilingPixel->renderHalfOfScreen(this->width, this->height);
}

void SdlWindow::render() { SDL_RenderPresent(this->renderer); }

SDL_Renderer* SdlWindow::getRenderer() const { return this->renderer; }
