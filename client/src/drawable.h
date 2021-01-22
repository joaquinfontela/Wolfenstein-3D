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

  Drawable() {}
  ~Drawable() {}
  Drawable(double x, double y, int id, int uniqueid = 0, double dist = INT_MAX) :
           x(x), y(y), id(id), dist(dist), uniqueid(uniqueid) {}
  virtual void draw(TextureManager& manager, double posX, double posY, double dirX,
                    double dirY, double planeX, double planeY, double* zBuffer);
  bool operator<(Drawable& other);
  void loadDistanceWithCoords(int px, int py);
  virtual bool hasThisUniqueId(int otherid);
  virtual bool isSprite();
 protected:
  Area srcArea, destArea;
};

#endif  // DRAWABLE_H_
