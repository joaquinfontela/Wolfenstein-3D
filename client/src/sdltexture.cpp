#include "sdltexture.h"

#include <SDL2/SDL_image.h>

#include <string>

#include "sdlexception.h"
#include "sdlwindow.h"

#define SDL_TEXTURE_LOAD_ERROR "\nTexture loading error: "

SdlTexture::SdlTexture(const std::string& filename, const SdlWindow& window)
    : renderer(window.getRenderer()) {
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

int SdlTexture::renderAll(const Area& src, const Area& dest) const {
  SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                      dest.getHeight()};
  return SDL_RenderCopy(this->renderer, this->texture, NULL, &sdlDest);
}

int SdlTexture::render(const Area& src, const Area& dest) const {
  SDL_Rect sdlSrc = {src.getX(), src.getY(), src.getWidth(), src.getHeight()};
  SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                      dest.getHeight()};
  return SDL_RenderCopy(this->renderer, this->texture, &sdlSrc, &sdlDest);
}
