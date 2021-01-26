#ifndef RAYCASTEDANIMATION_H_
#define RAYCASTEDANIMATION_H_

#include "clientprotocol.h"
#include "commandexecuter.h"
#include "drawable.h"
#include "texturemanager.h"

class RaycastedAnimation : public Drawable {
 public:
  RaycastedAnimation(double x, double y, CommandExecuter* executer, int itemId, int uniqueid, int framesPerAnimation) :
            Drawable(x, y, itemId, uniqueid), totalFrames(TIME_PER_ANIMATION_SLIDE * FRAMES_PER_EXPLOSION_ANIMATION), frames(-1), executer(executer), framesPerAnimation(framesPerAnimation), timePassed(0){}
  void draw(TextureManager& manager, double posX, double posY, double dirX,
            double dirY, double planeX, double planeY, double* zBuffer, float diff) override;
 private:
  int framesPerAnimation;
  int frames;
  int totalFrames;
  float timePassed;
  CommandExecuter* executer;
};

#endif  // RAYCASTEDANIMATION_H_
