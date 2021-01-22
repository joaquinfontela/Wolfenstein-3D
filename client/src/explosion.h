#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "clientprotocol.h"
#include "commandexecuter.h"
#include "drawable.h"
#include "texturemanager.h"

class Explosion : public Drawable {
 public:
  Explosion(double x, double y, CommandExecuter* executer, int uniqueid) :
            Drawable(x, y, EXPLOSION, uniqueid), remainingFrames(EXPLOSION_FRAMES),
            frames(-1), executer(executer) {}
  void draw(TextureManager& manager, double posX, double posY, double dirX,
            double dirY, double planeX, double planeY, double* zBuffer) override;
 private:
  int remainingFrames;
  int frames;
  CommandExecuter* executer;
};

#endif  // EXPLOSION_H_
