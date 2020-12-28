#ifndef DRAWABLE_H_
#define DRAWABLE_H_
#include "texturemanager.h"
#include "area.h"

#include <climits>

class Drawable {
 private:
  double x;
  double y;
  int id;
  double dist;
 public:
  Drawable() {}
  Drawable(double x, double y, int id, double dist = INT_MAX) : x(x), y(y), id(id), dist(dist) {}
  void draw(TextureManager& manager, double posX, double posY, double dirX, double dirY, double planeX, double planeY, double* zBuffer);
  bool operator<(Drawable& other);
  void loadDistanceWithCoords(int px, int py);
};

#endif  // DRAWABLE_H_
