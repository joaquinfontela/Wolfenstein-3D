#ifndef AREA_H_
#define AREA_H_

/**
 * @brief Represents a rectangle, where the (x,y) coordinates
 * show where the top left corner of the rectangle begins.
 *
 */
class Area {
 public:
  Area();

  /**
   * @brief Construct a new Area object
   *
   * @param x X coordinate of the top left corner.
   * @param y Y coordinate of the top left corner.
   * @param width Witdh of the box.
   * @param height Height of the box.
   */
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
