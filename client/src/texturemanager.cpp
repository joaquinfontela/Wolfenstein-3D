#include "texturemanager.h"

#include <iostream>
#include <map>

#include "area.h"
#include "sdltexture.h"
#define TEXTURE_LIMIT 64

#define TEXTURE_NOT_FOUND_ERROR "Error, texture not found with code: "
#define TEXTURE_FOUND_ERROR "Error, texture already found with code: "
#define TEXTURE_LIMIT_ERROR "Error, cannot add more textures with code: "
// Cambiar por una excepción.

void TextureManager::render(int id, Area srcArea, Area destArea) {
  std::map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    it->second->render(srcArea, destArea);
  else
    std::cerr << TEXTURE_NOT_FOUND_ERROR << id << std::endl;
}

void TextureManager::renderAll(int id, Area destArea) {
  std::map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    it->second->renderAll(destArea);
  else
    std::cerr << TEXTURE_NOT_FOUND_ERROR << id << std::endl;
}

void TextureManager::loadTexture(int id, SdlTexture* texture) {
  if (this->textures.size() > TEXTURE_LIMIT) {
    std::cout << TEXTURE_LIMIT_ERROR << std::endl;
  }
  std::map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    std::cerr << TEXTURE_FOUND_ERROR << id << std::endl;
  else
    this->textures[id] = texture;
}
