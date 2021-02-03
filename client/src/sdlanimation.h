#ifndef SDLANIMATION_H_
#define SDLANIMATION_H_

#include "area.h"
#include "drawable.h"
#include "texturemanager.h"

/**
 * @brief This class represents a non-raycasted which can be played at any time.
 *
 */
class SdlAnimation : public Drawable {
 public:
  /**
   * @brief Construct a new Sdl Animation object
   *
   * @param manager Reference to the texture manager.
   * @param slides Amount of frames the animation has.
   */
  SdlAnimation(TextureManager& manager, int slides)
      : pos(0),
        textureId(textureId),
        manager(manager),
        picsPerAnimation(slides) {}

  /**
   * @brief Sets new frame.
   *
   * @param newpos The next frame to be rendered will be: newpos % total number
   * of frames.
   */
  void updateFrame(int newpos);

  /**
   * @brief Updates the animation frame to the next one, or loops back to the
   * beginning if it goes out of bounds.
   *
   */
  void updateFrame();

  /**
   * @brief Given the width of the animation, it changes the value to the width
   * of one frame.
   *
   * @param width Width in pixels.
   */
  void setSlideWidth(int* width);

  /**
   * @brief Renders the stored frame to the screen.
   *
   * @param destArea Screen drawing area.
   * @param textureId Texture id to render.
   */
  void renderActualFrame(Area& destArea, int textureId);

 private:
  int pos;
  int textureId;
  TextureManager& manager;
  int picsPerAnimation;
};

#endif  // SDLANIMATION_H_
