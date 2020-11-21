#include "area.h"

Area::Area(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

int Area::getX() const { return this->x; }

int Area::getY() const { return this->y; }

int Area::getWidth() const { return this->width; }

int Area::getHeight() const { return this->height; }

void Area::moveLeft(int z) { x -= z; }

void Area::moveRight(int z) { x += z; }

void Area::moveUp(int z) { y += z; }

void Area::moveDown(int z) { y -= z; }

void Area::makeBigger(int z) {
  width += z;
  height += z;
}

void Area::makeSmaller(int z) {
  width -= z;
  height -= z;
}
