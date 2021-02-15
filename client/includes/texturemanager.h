#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <SDL2/SDL.h>

#include <unordered_map>
#include <string>

#include "area.h"
#include "sdltexture.h"
#include "sdlwindow.h"

/**
 * @brief Class used to organize the textures and stop duplicates from existing.
 *
 */
class TextureManager {
 public:
  /**
   * @brief Calls the garbage collector
   *
   */
  ~TextureManager();

  /**
   * @brief Construct a new Texture Manager object
   *
   * @param window Reference to the window.
   */
  TextureManager(SdlWindow* window);

  /**
   * @brief Calls the window render function. Updates the screen and draws over it.
   *
   */
  void updateScreen();

  /**
   * @brief Draws the game background.
   *
   */
  void drawBackground();

  /**
   * @brief Renders the texture, from the given id, to the screen. Throws an
   * Exception if it fails.
   *
   * @param id Texture id.
   * @param srcArea Area to crop from.
   * @param destArea Screen drawing area.
   */
  void render(int id, const Area& srcArea, const Area& destArea);

  /**
   * @brief Renders the whole texture, from the given id, to the screen. Throws
   * an Exception if it fails.
   *
   * @param id Texture id.
   * @param destArea Screen drawing area.
   */
  void renderAll(int id, const Area& destArea);

  /**
   * @brief Renders an entire image and fills all the screen with it.
   *
   */
  void renderComplete(int id);

  /**
   * @brief Stores the window size. Throws an Exception if it fails.
   *
   * @param w Pointer storing the width in pixels.
   * @param h Pointer storing the height in pixels.
   */
  void getWindowSize(int* w, int* h);

  /**
   * @brief Stores the texture (from the given id) size.
   *
   * @param w Pointer storing the width in pixels.
   * @param h Pointer storing the height in pixels.
   */
  void getTextureSizeWithId(int id, int* w, int* h);

  /**
   * @brief Renders the given text on the given area.
   *
   * @param text Text to render.
   * @param rect Rendering area.
   */
  void renderText(const char* text, SDL_Rect* rect);

  /**
   * @brief Returns a pointer to the SdlWindow.
   *
   * @return SdlWindow*
   */
  SdlWindow* accessWindow();

 private:
  SdlWindow* window;

  /**
   * @brief Loads all the textures needed for the game to be played.
   *
   */
  void loadTextures();

  /**
   * @brief Deletes all the textures created on init.
   *
   */
  void garbageCollector();

  /**
   * @brief Creates the texture from the name given and stores it on the texture
   * dictionary. If it fails it deallocates the resources and returns false.
   *
   * @param i Texture id.
   * @param name Texture file name.
   * @return true When no errors arise.
   * @return false If the texture couldn't be loaded or if it's stepping on
   * another id.
   */
  bool loadAndCheckTexture(int i, const std::string& name);

  /**
   * @brief Loads texture onto the texture dictionary.
   *
   * @param id Texture id.
   * @param texture
   * @return true when the operation is successful operation.
   * @return false if there is another texture loaded with the same id.
   */
  bool loadTexture(int id, SdlTexture* texture);

  std::unordered_map<int, SdlTexture*> textures;
};

#endif  // TEXTUREMANAGER_H_
