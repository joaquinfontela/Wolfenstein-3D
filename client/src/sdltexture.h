#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__
#include <SDL2/SDL_image.h>

#include <string>

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

/**
 * @brief Class that holds key information and methods from each texture used in
 * the game.
 *
 */
class SdlTexture {
 public:
  /**
   * @brief Construct a new Sdl Texture object from a file.
   *
   * @param filename Name of the file to open.
   * @param window Reference to the window.
   */
  SdlTexture(const std::string& filename, const SdlWindow& window);

  /**
   * @brief Construct a new Sdl Texture object from a surface.
   *
   * @param filename Name of the file to open.
   * @param window Reference to the window.
   */
  SdlTexture(SDL_Surface* surface, const SdlWindow& window);

  /**
   * @brief Destroy the Sdl Texture object releasing all the allocated
   * resources.
   *
   */
  ~SdlTexture();

  /**
   * @brief Renders the texture.
   *
   * @param src Source area to crop the texture.
   * @param dest Screen drawing area.
   * @return Returns SDL_RenderCopy's value.
   */
  int render(const Area& src, const Area& dest) const;

  /**
   * @brief Renders the entire texture.
   *
   * @param dest Screen drawing area.
   * @return Returns SDL_RenderCopy's value.
   */
  int renderAll(const Area& dest) const;

  /**
   * @brief Renders texture on the top half of its area (whose top left corner
   * matches the top left of the window)
   *
   * @param width
   * @param height
   * @return Returns SDL_RenderCopy's value.
   */
  int renderHalf(int width, int height) const;

  /**
   * @brief Renders the texture shifting src's x coordinate.
   *
   * @param sprite Value by which src.x is mutiplied
   * @param src Source area to crop the texture.
   * @param dest Screen drawing area.
   * @return Returns SDL_RenderCopy's value.
   */
  int renderOnTime(int sprite, const Area& src, const Area& dest) const;

  /**
   * @brief Get the texture size.
   *
   * @param w Pointer which will store the width.
   * @param h Pointer which will store the height.
   */
  void getSizes(int* w, int* h);

 private:
  /**
   * @brief Creates a texture instance. Throws an error if it fails.
   *
   * @param filename Name of the file to open.
   * @return SDL_Texture*
   */
  SDL_Texture* loadTexture(const std::string& filename);
  SDL_Renderer* renderer;
  SDL_Texture* texture;
};

#endif
