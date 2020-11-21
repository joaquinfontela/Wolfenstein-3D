#ifndef AREA_H_
#define AREA_H_

class Area {
 public:
  Area(int x, int y, int width, int height);
  int getX() const;
  int getY() const;
  int getWidth() const;
  int getHeight() const;
  void moveLeft(int z);
  void moveRight(int z);
  void moveUp(int z);
  void moveDown(int z);
  void makeBigger(int z);
  void makeSmaller(int z);

 private:
  int x;
  int y;
  int width;
  int height;
};

#endif  // AREA_H_
