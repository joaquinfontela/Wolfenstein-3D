#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>

class Coordinate {
 private:
  int x;
  int y;
  std::vector<int> vec;
 public:
  /**
   * @brief   Returns a coordinate at (x,y).
   */
  Coordinate(int x, int y);

  /**
   * @brief     Returns a new coordinate, where the first element of vec is x
   * and the second is y.
   */
  Coordinate(std::vector<int> vec);
  Coordinate();
  int getX();
  int getY();

  /**
   * @brief   Returns a vector with two elements, where the first is the X
   * component of  the coordinate, and the second is the Y component.
   */
  const std::vector<int>& getVector();
};

#endif
