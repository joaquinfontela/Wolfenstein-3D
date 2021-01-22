#ifndef RAYCASTEDANIMATION_H_
#define RAYCASTEDANIMATION_H_

#include "clientprotocol.h"
#include "commandexecuter.h"
#include "drawable.h"
#include "texturemanager.h"

class RaycastedAnimation : public Drawable {
 public:
  RaycastedAnimation(double x, double y, CommandExecuter* executer, int itemId, int uniqueid, int frames, int framesPerAnimation) :
            Drawable(x, y, itemId, uniqueid), remainingFrames(frames), frames(-1), executer(executer), framesPerAnimation(framesPerAnimation){}
  void draw(TextureManager& manager, double posX, double posY, double dirX,
            double dirY, double planeX, double planeY, double* zBuffer) override;
 private:
  int framesPerAnimation;
  int remainingFrames;
  int frames;
  CommandExecuter* executer;
};

#endif  // RAYCASTEDANIMATION_H_
