#include "../includes/area.h"

Area::Area() : x(0), y(0), width(0), height(0) {}

Area::Area(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

int Area::getX() const { return this->x; }

int Area::getY() const { return this->y; }

int Area::getWidth() const { return this->width; }

int Area::getHeight() const { return this->height; }

void Area::update(int newX, int newY, int newWidth, int newHeight) {
  this->x = newX;
  this->y = newY;
  this->width = newWidth;
  this->height = newHeight;
}
