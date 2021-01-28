#include "texturemanager.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "log.h"
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
                                   "bj4.png", // 16
                                   "bj5.png", // 17
                                   "bj6.png", // 18
                                   "bj7.png", // 19
                                   "hudguns.png", // 20
                                   "gunspritesrow.png", // 21
                                   "greystone.png", // 22
                                   "wood.png", // 23
                                   "door.png", // 24
                                   "1up.png", // 25
                                   "ammo.png", // 26
                                   "armor.png", // 27
                                   "basket.png", // 28
                                   "bed.png", // 29
                                   "blood.png", // 30
                                   "bloodyskeleton.png", // 31
                                   "bluekey.png", // 32
                                   "cage.png", // 33
                                   "cageskeleton.png", // 34
                                   "chaingunitem.png", // 35
                                   "chairandtable.png", // 36
                                   "chandelier.png", // 37
                                   "dogfood.png", // 38
                                   "emptywell.png", // 39
                                   "flag.png", // 40
                                   "floorlamp.png", // 41
                                   "flowerpot.png", // 42
                                   "food.png", // 43
                                   "chest.png", // 44
                                   "goldencross.png", // 45
                                   "goldencrown.png", // 46
                                   "goldencup.png", // 47
                                   "goldenkey.png", // 48
                                   "greenbarrel.png", // 49
                                   "groundskeleton.png", // 50
                                   "heapofbones.png", // 51
                                   "hungskeleton.png", // 52
                                   "lamp.png", // 53
                                   "machinegunitem.png", // 54
                                   "medkit.png", // 55
                                   "pillar.png", // 56
                                   "plant.png", // 57
                                   "pot.png", // 58
                                   "sink.png", // 59
                                   "spikes.png", // 60
                                   "stove.png", // 61
                                   "table.png", // 62
                                   "utensilholder.png", // 63
                                   "utensils.png", // 64
                                   "veins.png", // 65
                                   "water.png", // 66
                                   "well.png", // 67
                                   "mossy.png", // 68
                                   "redbrick.png", //69
                                   "purplestone.png", // 70
                                   "hudkey.png", // 71
                                   "rocketlauncheritem.png", // 72
                                   "flyingmissile.png", // 73
                                   "explosion.png", // 74
                                   "damage.png", // 75
                                   "dogdeath.png", // 76
                                   "soldierdeath.png", // 77
                                   "ssdeath.png", // 78
                                   "officialdeath.png", // 79
                                   "mutantdeath.png", // 80
                                   "dog_front.png", // 81
                                   "soldier_sprite_front.png", // 82
                                   "ss_front.png", // 83
                                   "official_front.png", // 84
                                   "mutant_front.png", // 85
                                   "dogsprint.png", // 86
                                   "soldiersprint.png", // 87
                                   "sssprint.png", // 88
                                   "officersprint.png", // 89
                                   "mutantsprint.png", // 90
                                   "dogattack.png", // 91
                                   "soldierattack.png", // 92
                                   "ssattack.png", // 93
                                   "officerattack.png", // 94
                                   "mutantattack.png", // 95
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
    LOG_WITH_ID(TEXTURE_NOT_FOUND_ERROR);
}

void TextureManager::getTextureSizeWithId(int id, int* w, int* h) {
  std::map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    it->second->getSizes(w, h);
  else
    LOG_WITH_ID(TEXTURE_NOT_FOUND_ERROR);
}

void TextureManager::renderAll(int id, const Area& destArea) {
  std::map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end())
    it->second->renderAll(destArea);
  else
    LOG_WITH_ID(TEXTURE_NOT_FOUND_ERROR);
}

void TextureManager::loadTexture(int id, SdlTexture* texture) {
  if (this->textures.size() > TEXTURE_LIMIT) {
    LOG_WITH_ID(TEXTURE_LIMIT_ERROR);
  }
  std::map<int, SdlTexture*>::iterator it = this->textures.find(id);
  if (it != this->textures.end()) {
    LOG_WITH_ID(TEXTURE_NOT_FOUND_ERROR);
  }
  else
    this->textures[id] = texture;
}
