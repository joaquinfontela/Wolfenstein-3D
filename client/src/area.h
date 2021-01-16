#ifndef AREA_H_
#define AREA_H_

class Area {
 public:
  Area();
  Area(int x, int y, int width, int height);
  void update(int newX, int newY, int newWidth, int newHeight);
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
