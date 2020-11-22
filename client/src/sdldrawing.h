#ifndef SDLDRAWING_H_
#define SDLDRAWING_H_

#include <string>

#include "area.h"
#include "sdltexture.h"
#include "sdlwindow.h"

class Drawing {
 private:
  SdlWindow& window;
  SdlTexture texture;
  Area srcArea;
  Area destArea;

 public:
  Drawing(std::string path, SdlWindow& window);
  Drawing(std::string path, SdlWindow& window, Area a, Area b);
  void moveLeft(int z);
  void moveRight(int z);
  void moveUp(int z);
  void moveDown(int z);
  void makeBigger(int z);
  void makeSmaller(int z);
  void draw();
};

#endif  // SDLDRAWING_H_
