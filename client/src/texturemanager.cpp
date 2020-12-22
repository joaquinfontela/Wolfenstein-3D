#include "texturemanager.h"

#include <iostream>
#include <map>

#include "area.h"
#include "sdltexture.h"

#define TEXTURE_NOT_FOUND_ERROR "Error, texture not found with code: "
#define TEXTURE_FOUND_ERROR "Error, texture already found with code: "
// Cambiar por una excepción.

void TextureManager::render(int img, Area srcArea, Area destArea) {
  std::cout << "tengo : " << textures.size() << " texturas cargadas." << std::endl;
  std::map<int, SdlTexture*>::iterator it = this->textures.find(img);
  if (it != this->textures.end()){
    it->second->render(srcArea, destArea);
  }

  else
    std::cerr << TEXTURE_NOT_FOUND_ERROR << img << std::endl;
}

void TextureManager::renderAll(int img, Area destArea) {
  std::map<int, SdlTexture*>::iterator it = this->textures.find(img);
  if (it != this->textures.end())
    it->second->renderAll(destArea);
  else
    std::cerr << TEXTURE_NOT_FOUND_ERROR << img << std::endl;
}

void TextureManager::loadTexture(int img, SdlTexture* texture) {
  std::map<int, SdlTexture*>::iterator it = this->textures.find(img);
  if (it != this->textures.end())
    std::cerr << TEXTURE_FOUND_ERROR << img << std::endl;
  else
    this->textures[img] = texture;
}
