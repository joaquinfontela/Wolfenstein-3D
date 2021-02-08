#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>

class Coordinate {
 private:
  int x;
  int y;

 public:
  // Returns a coordinate at (x,y).
  Coordinate(int x, int y);

  // Returns a new coordinate, where the first element of vec is x, and the
  // second is y.
  Coordinate(std::vector<int> vec);
  Coordinate();
  int getX();
  int getY();

  // Returns a vector with two elements, where the first is the X component of
  // the coordinate, and the second is the Y component.
  std::vector<int> getVector();
};

#endif