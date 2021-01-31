#ifndef DRAWABLE_H_
#define DRAWABLE_H_
#include "texturemanager.h"
#include "area.h"

#include <climits>

class Drawable {
 public:
  double x;
  double y;
  int id;
  double dist;
  int uniqueid;
  bool hasToBeDeleted;

  Drawable() {}
  ~Drawable() {}
  Drawable(double x, double y, int id, int uniqueid = 0, double dist = INT_MAX) :
           x(x), y(y), id(id), dist(dist), uniqueid(uniqueid), hasToBeDeleted(false) {}
  virtual void draw(TextureManager& manager, double posX, double posY, double dirX,
                    double dirY, double planeX, double planeY, double* distanceBuffer, float diff);
  bool operator<(Drawable& other);
  bool isContained(double* distanceBuffer, double posX, double posY, double dirX,
                   double dirY, double planeX, double planeY, int width, int height);
  void loadDistanceWithCoords(int px, int py);
  virtual bool hasThisUniqueId(int otherid);
  virtual bool isSprite();
  virtual bool isPlayer();

 protected:
  void calculateDrawingData(int& spriteScreen, int& spriteWidth, int& spriteHeight, int& drawStart,
                            int& drawEnd, double& transformY, double posX, double posY, double planeX,
                            double planeY, double dirX, double dirY, int width, int height);
  Area srcArea, destArea;
};

#endif  // DRAWABLE_H_
