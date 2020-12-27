#ifndef RAYCASTER_H_
#define RAYCASTER_H_
#include "sdlwindow.h"

#include "texturemanager.h"
#include "../../common/includes/Map/Map.h"
#include "../../common/includes/Thread/Thread.h"

#include <atomic>

#define PI 3.14159265359

class Raycaster : public Thread {
 public:
  Raycaster(double width, double height, TextureManager& manager, Map& m, std::atomic<bool>& b, SdlWindow* window) :
          alive(b), width(width) , height(height) , manager(manager) , matrix(m) ,  window(window) {}
  void run();
 private:
  std::atomic<bool>& alive;
  double width;
  double height;
  TextureManager& manager;
  Map& matrix;
  double distanceToProyection = floor((width/2)/(tan((PI/2) - PI/3)));
  SdlWindow* window;
};

#endif  // RAYCASTER_H_
