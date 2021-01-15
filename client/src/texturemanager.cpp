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
                                   "bj3.png", // 15
                                   "hudguns.png", // 16
                                   "gunspritesrow.png", // 17
                                   "greystone.png", // 18
                                   "wood.png", // 19
                                   "door.png", // 20
                                   "1up.png", // 21
                                   "ammo.png", // 22
                                   "armor.png", // 23
                                   "basket.png", // 24
                                   "bed.png", // 25
                                   "blood.png", // 26
                                   "bloodyskeleton.png", // 27
                                   "bluekey.png", // 28
                                   "cage.png", // 29
                                   "cageskeleton.png", // 30
                                   "chaingunitem.png", // 31
                                   "chairandtable.png", // 32
                                   "chandelier.png", // 33
                                   "dogfood.png", // 34
                                   "emptywell.png", // 35
                                   "flag.png", // 36
                                   "floorlamp.png", // 37
                                   "flowerpot.png", // 38
                                   "food.png", // 39
                                   "chest.png", // 40
                                   "goldencross.png", // 41
                                   "goldencrown.png", // 42
                                   "goldencup.png", // 43
                                   "goldenkey.png", // 44
                                   "greenbarrel.png", // 45
                                   "groundskeleton.png", // 46
                                   "heapofbones.png", // 47
                                   "hungskeleton.png", // 48
                                   "lamp.png", // 49
                                   "machinegunitem.png", // 50
                                   "medkit.png", // 51
                                   "pillar.png", // 52
                                   "plant.png", // 53
                                   "pot.png", // 54
                                   "sink.png", // 55
                                   "spikes.png", // 56
                                   "stove.png", // 57
                                   "table.png", // 58
                                   "utensilholder.png", // 59
                                   "utensils.png", // 60
                                   "veins.png", // 61
                                   "water.png", // 62
                                   "well.png", // 63
                                   "mossy.png", // 64
                                   "redbrick.png", //65
                                   "purplestone.png" // 66
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

void TextureManager::render(int id, const Area& srcArea, const Area& destArea) {
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

void TextureManager::renderAll(int id, const Area& destArea) {
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
