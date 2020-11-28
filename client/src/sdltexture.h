#ifndef SDLTEXTURE_H_
#define SDLTEXTURE_H_
#include <string>

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

class SdlTexture {
 public:
  SdlTexture() {}
  SdlTexture(const std::string& filename, const SdlWindow& window);
  void setTexture(const std::string& filename, const SdlWindow& window);
  ~SdlTexture();
  int renderAll(const Area& dest) const; 
  int render(const Area& src, const Area& dest) const;
  SdlTexture& operator=(SdlTexture&& other);
  SdlTexture(SdlTexture&& other);

 private:
  SDL_Texture* loadTexture(const std::string& filename);
  SDL_Renderer* renderer;
  SDL_Texture* texture;
};

#endif  // SDLTEXTURE_H_
