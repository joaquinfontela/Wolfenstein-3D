#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include "sdlexception.h"
#include "sdlwindow.h"
#include <iostream>

#define SDL_INIT_ERROR "\nError on initialization: "
#define SDL_WINDOW_INIT_ERROR "\nError on window initialization: "

#define IMG_PATH "../../media/"

SdlWindow::SdlWindow(int width, int height) :
                     width(width), height(height) {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    throw SdlException(SDL_INIT_ERROR, SDL_GetError());
  }
  if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
      &this->window, &this->renderer)) {
    throw SdlException(SDL_WINDOW_INIT_ERROR, SDL_GetError());
  }   
  SDL_SetWindowTitle(this->window,"Wolfenstein");
  SDL_Surface* icon = IMG_Load(IMG_PATH "wolfensteinlogo.jpg");
  SDL_SetWindowIcon(this->window,icon);
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


SdlWindow::~SdlWindow() {
  this->killRenderer();
  this->killWindow();
}
 
void SdlWindow::fillTransparent(int r, int g, int b) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, 1);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() { this->fill(0,0,0,0.9); }

void SdlWindow::render() { SDL_RenderPresent(this->renderer); }

SDL_Renderer* SdlWindow::getRenderer() const { return this->renderer; }

