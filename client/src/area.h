#ifndef AREA_H_
#define AREA_H_

class Area {
 public:
  Area(int x, int y, int width, int height);
  int getX() const;
  int getY() const;
  int getWidth() const;
  int getHeight() const;
 private:
  int x;
  int y;
  int width;
  int height;
};

#endif

