#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__
#include <SDL2/SDL_ttf.h>

#include "area.h"
#include "sdltexture.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

/**
 * @brief Inits the key functions to open audio and video. Manages rendering
 * calls. Keeps the reference to the SDL_Window and SDL_Renderer.
 *
 */
class SdlWindow {
 public:
  /**
   * @brief Construct a new Sdl Window object. Initializes the window, audio and
   * renderer for the game. Throws an SdlException in case anything fails.
   *
   * @param width Screen width in pixels.
   * @param height Screen height in pixels.
   */
  SdlWindow(int width, int height);

  /**
   * @brief Destroy the Sdl Window object. Returns the allocated resources from
   * the renderer, window and audio system.
   *
   */
  ~SdlWindow();

  /**
   * @brief When summoned, switches the window to fullscreen mode. 
   * @returns int sdl fullScreen return code.
   */
  int goFullScreen();

  /**
   * @brief Sets renderer rgb and alpha values.
   *
   * @param r Red amount.
   * @param g Green amount.
   * @param b Blue amount.
   * @param alpha Alpha amount.
   */
  void fill(int r, int g, int b, int alpha);

  /**
   * @brief Changes renderer color to black.
   *
   */
  void fill();

  /**
   * @brief Draws background colors for the game.
   *
   */
  void fillWolfenstein();

  /**
   * @brief Renders the data stored in SDL's buffer.
   *
   */
  void render();

  /**
   * @brief Stores the windows witdh and height on the given pointers.
   *
   * @param w Screen width in pixels.
   * @param h Screen height in pixels.
   */
  void getWindowSize(int* w, int* h);

  /**
   * @brief Renders the given text on the given area.
   *
   * @param text Text to render.
   * @param rect Rendering area.
   */
  void renderText(const char* text, SDL_Rect* rect);

  /**
   * @brief Get the Renderer object.
   *
   * @return SDL_Renderer*
   */
  SDL_Renderer* getRenderer() const;
  void playOrStopAudio();

 private:
  /**
   * @brief Deletes the resources taken by the renderer.
   *
   */
  void killRenderer();

  /**
   * @brief Deletes the resources taken by the window,
   *
   */
  void killWindow();

  /**
   * @brief Deletes the resources taken by the audio system.
   *
   */
  void killAudio();

  int width;

  /**
   * @brief Game font.
   *
   */
  TTF_Font* font;
  int height;
  SDL_Window* window;
  SDL_Renderer* renderer;

  /**
   * @brief 1px texture needed to draw the ceiling in the game.
   *
   */
  SdlTexture* ceilingPixel;
};

#endif
