#include "texturemanager.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "area.h"
#include "sdltexture.h"
#include "sdlexception.h"
#include "clientprotocol.h"

#define SDL_TEXTURE_INIT_ERROR "Error, couldn't be opened. "
#define TEXTURE_NOT_FOUND_ERROR "Error, texture not found with code: "
#define TEXTURE_FOUND_ERROR "Error, texture already found with code: "
#define TEXTURE_LIMIT_ERROR "Error, cannot add more textures with code: "
// Cambiar por una excepción.

void TextureManager::getWindowSize(int* w, int* h) {
  return this->window->getWindowSize(w,h);
}

void TextureManager::garbageCollector() {
  for (std::map<int, SdlTexture*>::iterator it = this->textures.begin(); it != this->textures.end(); ++it) {
    delete it->second;
  }
}

bool TextureManager::loadAndCheckTexture(int i, const std::string& name) {
  SdlTexture* text = new SdlTexture((IMG_PATH + name).c_str(), *window);
  if (text == NULL) {
    return false;
  }
  this->loadTexture(i, text);
  return true;
}

TextureManager::~TextureManager() {
  this->garbageCollector();
}

void TextureManager::loadTextures() {
  std::vector<std::string> names({ "wall.png", // 1
                                   "wall2.png", // 2
                                   "guard.png", // 3
                                   "chaingun2.png", // 4
                                   "hud.png", // 5
                                   "greenlight.png", // 6
                                   "smallbarrel.png", // 7
                                   "soldierfront.png", // 8
                                   "soldierright.png", // 9
                                   "soldierback.png", // 10
                                   "soldierleft.png", // 11
                                   "hitlerwall.png", // 12
                                   "bj1.png", // 13
                                   "bj2.png", // 14
                                   "bj3.png" // 15
                                  });
  int i = 1;
  for (std::string& name : names) {
    if (!this->loadAndCheckTexture(i,name)){
      this->garbageCollector();
      throw SdlException(SDL_TEXTURE_INIT_ERROR, SDL_GetError());
      break;
    }
    i++;
  }
}

void TextureManager::render(int id, Area srcArea, Area destArea) {
  std::map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    it->second->render(srcArea, destArea);
  else
    std::cerr << TEXTURE_NOT_FOUND_ERROR << id << std::endl;
}

void TextureManager::getTextureSizeWithId(int id, int* w, int* h) {
  std::map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    it->second->getSizes(w, h);
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
