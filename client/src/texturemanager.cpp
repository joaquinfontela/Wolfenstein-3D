#include "../includes/texturemanager.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../includes/fileloader.h"
#include "../includes/area.h"
#include "../includes/clientprotocol.h"
#include "../includes/sdlexception.h"
#include "../includes/sdltexture.h"

#define SDL_TEXTURE_INIT_ERROR "Error, couldn't be opened. "
#define TEXTURE_NOT_FOUND_ERROR "Error, texture not found with code: "
#define TEXTURE_FOUND_ERROR "Error, texture already found with code: "
#define TEXTURE_LIMIT_ERROR "Error, cannot add more textures with code: "
// Cambiar por una excepción.

void TextureManager::drawBackground() {
  return this->window->fillWolfenstein();
}

void TextureManager::updateScreen() {
  return this->window->render();
}

void TextureManager::renderText(const char* text, SDL_Rect* rect) {
  return this->window->renderText(text, rect);
}

void TextureManager::getWindowSize(int* w, int* h) {
  return this->window->getWindowSize(w, h);
}

void TextureManager::garbageCollector() {
  for (std::unordered_map<int, SdlTexture*>::iterator it =
           this->textures.begin();
       it != this->textures.end(); ++it) {
    delete it->second;
  }
}

void TextureManager::renderComplete(int id) {
  int width, height;
  this->window->getWindowSize(&width, &height);
  Area dest(0, 0, width, height);
  this->renderAll(id, dest);
}

bool TextureManager::loadAndCheckTexture(int i, const std::string& name) {
  SdlTexture* text = new SdlTexture((IMG_PATH + name).c_str(), *window);
  if (text == NULL || !this->loadTexture(i, text)) {
    delete text;
    return false;
  }
  return true;
}

SdlWindow* TextureManager::accessWindow() { return this->window; }

TextureManager::~TextureManager() { this->garbageCollector(); }

TextureManager::TextureManager(SdlWindow* window) : window(window) {
  this->loadTextures();
}

void TextureManager::loadTextures() {
  std::vector<std::string> names;
  FileLoader::loadFromFile(names, IMG_PATH "imglist.txt");
  int i = 1;
  for (std::string& name : names) {
    if (!this->loadAndCheckTexture(i, name)) {
      this->garbageCollector();
      throw SdlException(SDL_TEXTURE_INIT_ERROR, SDL_GetError());
      break;
    }
    i++;
  }
}

void TextureManager::render(int id, const Area& srcArea, const Area& destArea) {
  std::unordered_map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    it->second->render(srcArea, destArea);
  else
    LOG_WITH_ID(TEXTURE_NOT_FOUND_ERROR);
}

void TextureManager::getTextureSizeWithId(int id, int* w, int* h) {
  std::unordered_map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    it->second->getSizes(w, h);
  else
    LOG_WITH_ID(TEXTURE_NOT_FOUND_ERROR);
}

void TextureManager::renderAll(int id, const Area& destArea) {
  std::unordered_map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    it->second->renderAll(destArea);
  else
    LOG_WITH_ID(TEXTURE_NOT_FOUND_ERROR);
}

bool TextureManager::loadTexture(int id, SdlTexture* texture) {
  if (this->textures.size() > TEXTURE_LIMIT) {
    LOG_WITH_ID(TEXTURE_LIMIT_ERROR);
  }
  if (this->textures.find(id) != this->textures.end()) {
    LOG_WITH_ID(TEXTURE_FOUND_ERROR);
    return false;
  } else {
    this->textures[id] = texture;
    return true;
  }
}
