#ifndef HUDANIMATIONS_H_
#define HUDANIMATIONS_H_

#include "sdlanimation.h"
#include "texturemanager.h"

/**
 * @brief RAII Wrapper for the SldAnimation.
 *
 */
class HudAnimations {
 public:
  SdlAnimation* animation;
  HudAnimations(TextureManager& manager, int code);
  ~HudAnimations();
};

#endif  // HUDANIMATIONS_H_
