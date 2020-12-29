#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include "sdlexception.h"
#include "sdlwindow.h"
#include "sdltexture.h"
#include <iostream>

#define SDL_INIT_ERROR "\nError on initialization: "
#define SDL_WINDOW_INIT_ERROR "\nError on window initialization: "
#define CEILING_COLOR 0x7B, 0x7B, 0x7B
#define FLOOR_COLOR 0x60, 0x60, 0x60
#define OTHER_COLOR 0xFF, 0xFF, 0x60
#define IMG_PATH "../media/"
#define AUDIO_PATH "../audio/"

SdlWindow::SdlWindow(int width, int height) :
                     width(width), height(height) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    throw SdlException(SDL_INIT_ERROR, SDL_GetError());
  }
  if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
      &this->window, &this->renderer)) {
    throw SdlException(SDL_WINDOW_INIT_ERROR, SDL_GetError());
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
    throw SdlException(Mix_GetError());
  }
  this->audio = Mix_LoadMUS(AUDIO_PATH "song.mp3");
  SDL_SetWindowTitle(this->window,"Wolfenstein");
  SDL_Surface* icon = IMG_Load(IMG_PATH "wolfensteinlogo.jpg");
  SDL_SetWindowIcon(this->window,icon);
}

void SdlWindow::getWindowSize(int* w, int* h) {
  SDL_GetWindowSize(this->window, &this->width, &this->height);
  *w = this->width;
  *h = this->height;
}

void SdlWindow::playOrStopAudio(){
  if (!Mix_PlayingMusic())
    Mix_PlayMusic(this->audio, 1);
  else if (Mix_PausedMusic())
    Mix_ResumeMusic();
  else
    Mix_PauseMusic();
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
  if (!this->window) return;
  Mix_FreeMusic(this->audio);
  Mix_CloseAudio();
  Mix_Quit();
}

SdlWindow::~SdlWindow() {
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
  SdlTexture im(IMG_PATH "ceiling.png", *this);
  // Hacer que ^^ esta textura sea un atributo para evitar múltiples cargas.
  im.renderHalfOfScreen(this->width, this->height);
}

void SdlWindow::render() { SDL_RenderPresent(this->renderer); }

SDL_Renderer* SdlWindow::getRenderer() const { return this->renderer; }
