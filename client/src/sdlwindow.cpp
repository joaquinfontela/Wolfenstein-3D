#include "../includes/sdlwindow.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "../includes/clientprotocol.h"
#include "../includes/sdlexception.h"
#include "../includes/sdltexture.h"

#define SDL_INIT_ERROR "\nError on initialization: "
#define SDL_CEILING_INIT_ERROR "\nError on ceiling texture initialization "
#define SDL_WINDOW_INIT_ERROR "\nError on window initialization: "
#define TTF_INIT_ERROR "\nError on initialization: "

SdlWindow::SdlWindow(int width, int height) : width(width), height(height) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    throw SdlException(SDL_INIT_ERROR, SDL_GetError());
  }
  if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
                                  &this->window, &this->renderer)) {
    throw SdlException(SDL_WINDOW_INIT_ERROR, SDL_GetError());
  }
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2024) < 0) {
    throw SdlException(Mix_GetError());
  }
  if (!(ceilingPixel = new SdlTexture(IMG_PATH "ceiling.png", *this))) {
    throw SdlException(SDL_CEILING_INIT_ERROR, SDL_GetError());
  }
  if (TTF_Init() < 0 ||
      !(this->font = TTF_OpenFont(FONT_PATH GAME_FONT, 100))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  Mix_AllocateChannels(32);
  SDL_SetWindowTitle(this->window, GAME_TITLE);
  SDL_Surface* icon = IMG_Load(IMG_PATH GAME_LOGO);
  SDL_SetWindowIcon(this->window, icon);
  this->width = width;
  this->height = height;
}

int SdlWindow::goFullScreen() {
  SDL_DisplayMode dm;
  if (SDL_GetDesktopDisplayMode(0,&dm) != 0) {
    LOG(SDL_GetError());
  } else {
    this->width = dm.w;
    this->height = dm.h;
  }
  return SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void SdlWindow::renderText(const char* text, SDL_Rect* rect) {
  SDL_Texture* texture = nullptr;
  SDL_Surface* surface = nullptr;
  SDL_Color color = {GREY};
  if (!(surface = TTF_RenderText_Solid(this->font, text, color))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  if (!(texture = SDL_CreateTextureFromSurface(this->renderer, surface))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  SDL_RenderCopy(this->renderer, texture, NULL, rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void SdlWindow::getWindowSize(int* w, int* h) {
  *w = this->width;
  *h = this->height;
}

void SdlWindow::killRenderer() {
  if (!this->renderer) return;
  SDL_DestroyRenderer(this->renderer);
  this->renderer = NULL;
}

void SdlWindow::killWindow() {
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
  TTF_CloseFont(this->font);
  TTF_Quit();
  SDL_Quit();
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
  SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
  SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() { this->fill(0, 0, 0, 0); }

void SdlWindow::fillWolfenstein() {
  this->fill(FLOOR_COLOR, 0);
  this->ceilingPixel->renderHalf(this->width, this->height);
}

void SdlWindow::render() { SDL_RenderPresent(this->renderer); }

SDL_Renderer* SdlWindow::getRenderer() const { return this->renderer; }
