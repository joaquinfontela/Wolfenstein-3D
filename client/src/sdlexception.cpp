#include "../includes/sdlexception.h"

#include <SDL2/SDL_image.h>

#include <string>

SdlException::SdlException(const char* description, const char* sdlError)
    : std::exception(), description(description) {
  this->description.append(sdlError);
}

SdlException::SdlException(const char* sdlError)
    : std::exception(), description("") {
  this->description.append(sdlError);
}

const char* SdlException::what() const noexcept {
  return this->description.c_str();
}
