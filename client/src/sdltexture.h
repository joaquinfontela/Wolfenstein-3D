#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__
#include <string>
#include <SDL2/SDL_image.h>

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

class SdlTexture {
 public:
  SdlTexture(const std::string& filename, const SdlWindow& window);
  SdlTexture(SDL_Surface* surface, const SdlWindow& window);
  ~SdlTexture();
  int render(const Area& src, const Area& dest) const;
  int renderAll(const Area& dest) const;
  int renderHalfOfScreen(int width, int height) const;
  int renderOnTime(int sprite, const Area& src, const Area& dest) const;
  void getSizes(int* w, int* h);
 private:
  SDL_Texture* loadTexture(const std::string& filename);
  SDL_Renderer* renderer;
  SDL_Texture* texture;
};

#endif
