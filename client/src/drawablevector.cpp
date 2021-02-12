#include "../includes/drawablevector.h"

#include <algorithm>

#include "../includes/clientprotocol.h"
#include "../includes/texturemanager.h"

void DrawableVector::raycastSprites(double x, double y, double dirX,
                                    double dirY, double planeX, double planeY,
                                    double* distanceBuffer, float drawableDiff,
                                    TextureManager& manager) {
  std::unique_lock<std::mutex> lock(this->lock);
  for (Drawable* d : this->sprites) {
    d->loadDistanceWithCoords(x, y);
  }
  std::sort(this->sprites.begin(), this->sprites.end(),
            [](Drawable* a, Drawable* b) -> bool { return *a < *b; });

  std::vector<Drawable*>::iterator it = this->sprites.begin();

  while (it != this->sprites.end()) {
    if (!(*it)->hasToBeDeleted) {
      (*it)->draw(manager, x, y, dirX, dirY, planeX, planeY, distanceBuffer,
                  drawableDiff);
      ++it;
    } else {
      delete (*it);
      this->sprites.erase(it);
    }
  }
}

DrawableVector::~DrawableVector() {
  this->garbageCollector();
}

void DrawableVector::garbageCollector() {
  for (Drawable* s : this->sprites) {
    delete s;
  }
}

void DrawableVector::push_back(Drawable* drawable) {
  if (!drawable) {
    LOG("Error, can't push a null pointer as a sprite.");
  } else {
   this->sprites.push_back(drawable);
  }
}

void DrawableVector::removeSpriteWithIdAndGetSound(uint32_t itemId,
                                                   uint32_t* soundId) {
  std::unique_lock<std::mutex> lock(this->lock);
  std::vector<Drawable*>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end(); ++it) {
    if ((*it)->hasThisUniqueId(itemId)) {
      int soundid = (*it)->id;
      delete (*it);
      this->sprites.erase(it);
      if (IS_HEALTH_UP(soundid)) {
        *soundId = HEALTH_PICKUP_SOUND;
      } else {
        *soundId = PICKUP_SOUND;
      }
      break;
    }
  }
}

void DrawableVector::swapCoords(double x, double y, uint32_t itemId) {
  std::unique_lock<std::mutex> lock(this->lock);
  std::vector<Drawable*>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end(); ++it) {
    if ((*it)->hasThisUniqueId(itemId)) {
      (*it)->x = x;
      (*it)->y = y;
      break;
    }
  }
}

void DrawableVector::getCoordsAndErase(double* x, double* y, uint32_t itemId) {
  std::unique_lock<std::mutex> lock(this->lock);
  std::vector<Drawable*>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end(); ++it) {
    if ((*it)->hasThisUniqueId(itemId)) {
      *x = (*it)->x;
      *y = (*it)->y;
      delete (*it);
      this->sprites.erase(it);
      break;
    }
  }
}

void DrawableVector::popAndErase(Drawable* toKill) {
  std::unique_lock<std::mutex> lock(this->lock);
  std::vector<Drawable*>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end(); ++it) {
    if (*it == toKill) {
      this->sprites.erase(it);
      break;
    }
  }
}
