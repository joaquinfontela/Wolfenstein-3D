#include "../includes/sdlanimation.h"
#include "../includes/HudAnimations.h"
#include "../includes/texturemanager.h"

#include <string>

#define ANIMATION_CREATING_ERROR "Error crating the animation with code: "

HudAnimations::HudAnimations(TextureManager& manager, int code) {
  if ((this->animation = new SdlAnimation(manager, code)) == nullptr) {
    std::string error = ANIMATION_CREATING_ERROR;
    error += std::to_string(code);
    throw std::runtime_error(error);
  }
}

HudAnimations::~HudAnimations() {
  delete this->animation;
}
