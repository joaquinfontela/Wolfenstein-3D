#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>

class Coordinate {
 private:
  int x;
  int y;

 public:
  Coordinate(int x, int y);
  Coordinate(std::vector<int> vec);
  Coordinate();
  int getX();
  int getY();
  std::vector<int> getVector();
};

#endif