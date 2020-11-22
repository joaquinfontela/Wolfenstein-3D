#include "sdldrawing.h"

#include "sdltexture.h"
#include "sdlwindow.h"

Drawing::Drawing(std::string path, SdlWindow& window) : window(window) {
  SdlTexture t(path, this->window);
  this->texture = std::move(t);
}

// Ojo que paso siempre por copia el area.
// Puede que no siempre sea conveniente.
Drawing::Drawing(std::string path, SdlWindow& window, Area a, Area b)
    : window(window), srcArea(a), destArea(b) {
  SdlTexture t(path, this->window);
  this->texture = std::move(t);
}

void Drawing::moveLeft(int z) { this->destArea.moveLeft(z); }

void Drawing::moveRight(int z) { this->destArea.moveRight(z); }

void Drawing::moveUp(int z) { this->destArea.moveUp(z); }

void Drawing::moveDown(int z) { this->destArea.moveDown(z); }

void Drawing::makeBigger(int z) { this->destArea.makeBigger(z); }

void Drawing::makeSmaller(int z) { this->destArea.makeSmaller(z); }

void Drawing::draw() { this->texture.render(srcArea, destArea); }