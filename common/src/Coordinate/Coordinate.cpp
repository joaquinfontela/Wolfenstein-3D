#include "../../includes/Coordinate/Coordinate.h"

Coordinate::Coordinate(int x, int y) {
  this->x = x;
  this->y = y;
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

std::vector<int> Coordinate::getVector() {
  std::vector<int> vec;
  vec.push_back(this->x);
  vec.push_back(this->y);
  return vec;
}