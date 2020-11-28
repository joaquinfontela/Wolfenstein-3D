#include "sdltexture.h"

#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>

#include "sdlexception.h"
#include "sdlwindow.h"

#define SDL_TEXTURE_LOAD_ERROR "\nTexture loading error: "

SdlTexture& SdlTexture::operator=(SdlTexture&& other) {
  std::cout << "Llamando al = por movimiento de la textura.\n";
  if (this != &other) {
    this->renderer = other.renderer;
    this->texture = other.texture;
    other.renderer = nullptr;
    other.texture = nullptr;
  }
  return *this;
}

SdlTexture::SdlTexture(SdlTexture&& other) {
  std::cout << "Llamando al constrcutor por movimiento de la textura.\n";
  this->renderer = other.renderer;
  this->texture = other.texture;
  other.renderer = nullptr;
  other.texture = nullptr;
}

void SdlTexture::setTexture(const std::string& filename,
                            const SdlWindow& window) {
  this->renderer = window.getRenderer();
  this->texture = loadTexture(filename);
}

SdlTexture::SdlTexture(const std::string& filename, const SdlWindow& window)
    : renderer(window.getRenderer()) {
  std::cout << "Llamando al constrcutor feo de la textura.\n";
  this->texture = loadTexture(filename);
}

SdlTexture::~SdlTexture() { SDL_DestroyTexture(this->texture); }

SDL_Texture* SdlTexture::loadTexture(const std::string& filename) {
  SDL_Texture* text = IMG_LoadTexture(this->renderer, filename.c_str());
  if (!text) {
    throw SdlException(SDL_TEXTURE_LOAD_ERROR, SDL_GetError());
  }
  return text;
}

int SdlTexture::render(const Area& src, const Area& dest) const {
  SDL_Rect sdlSrc = {src.getX(), src.getY(), src.getWidth(), src.getHeight()};
  SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                      dest.getHeight()};
  return SDL_RenderCopy(this->renderer, this->texture, &sdlSrc, &sdlDest);
}

int SdlTexture::renderAll(const Area& dest) const {
  SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                      dest.getHeight()};
  return SDL_RenderCopy(this->renderer, this->texture, NULL, &sdlDest);
}
