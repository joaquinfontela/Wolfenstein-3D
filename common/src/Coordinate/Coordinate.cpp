#include "../../includes/Coordinate/Coordinate.h"

Coordinate::Coordinate(int x, int y) {
  this->x = x;
  this->y = y;
  this->vec.push_back(x);
  this->vec.push_back(y);
}

Coordinate::Coordinate() {
  this->x = 0;
  this->y = 0;
}

Coordinate::Coordinate(std::vector<int> vec) {
  if (vec.size() != 2) std::__throw_runtime_error("Vector size is not 2.");
  this->x = vec[0];
  this->y = vec[1];
}

int Coordinate::getX() { return this->x; }

int Coordinate::getY() { return this->y; }

const std::vector<int>& Coordinate::getVector() {
  return vec;
}
