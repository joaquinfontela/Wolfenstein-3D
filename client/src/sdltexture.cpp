#include "../includes/sdltexture.h"

#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>

#include "../includes/sdlexception.h"
#include "../includes/sdlwindow.h"

#define SDL_TEXTURE_LOAD_ERROR "\nTexture loading error: "

void SdlTexture::getSizes(int* w, int* h) {
  SDL_QueryTexture(this->texture, NULL, NULL, w, h);
}

SdlTexture::SdlTexture(const std::string& filename, const SdlWindow& window)
    : renderer(window.getRenderer()) {
  this->texture = loadTexture(filename);
}

SdlTexture::SdlTexture(SDL_Surface* surface, const SdlWindow& window) {
  this->texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
  if (!this->texture) {
    throw SdlException(SDL_TEXTURE_LOAD_ERROR, SDL_GetError());
  }
}

SdlTexture::~SdlTexture() { SDL_DestroyTexture(this->texture); }

SDL_Texture* SdlTexture::loadTexture(const std::string& filename) {
  SDL_Texture* text = IMG_LoadTexture(this->renderer, filename.c_str());
  if (!text) {
    throw SdlException(SDL_TEXTURE_LOAD_ERROR, SDL_GetError());
  }
  return text;
}

int SdlTexture::renderAll(const Area& dest) const {
  SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                      dest.getHeight()};
  return SDL_RenderCopy(this->renderer, this->texture, NULL, &sdlDest);
}

int SdlTexture::renderHalf(int width, int height) const {
  SDL_Rect sdlDest = {0, 0, width, height / 2};
  return SDL_RenderCopy(this->renderer, this->texture, NULL, &sdlDest);
}

int SdlTexture::render(const Area& src, const Area& dest) const {
  SDL_Rect sdlSrc = {src.getX(), src.getY(), src.getWidth(), src.getHeight()};
  SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                      dest.getHeight()};
  return SDL_RenderCopy(this->renderer, this->texture, &sdlSrc, &sdlDest);
}

int SdlTexture::renderOnTime(int sprite, const Area& src,
                             const Area& dest) const {
  SDL_Rect sdlSrc = {src.getX() * sprite, src.getY(), src.getWidth(),
                     src.getHeight()};
  SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                      dest.getHeight()};
  return SDL_RenderCopy(this->renderer, this->texture, &sdlSrc, &sdlDest);
}
