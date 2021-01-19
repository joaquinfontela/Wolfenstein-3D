#include "sdlexception.h"
#include "clientprotocol.h"
#include "audiomanager.h"
#include <vector>
#include <string>
#include <iostream>

#define TRACK_INIT_ERROR "Error, track already found: "
#define TRACK_NOT_FOUND_ERROR "Error, track not found with code: "
#define AUDIO_PATH "../audio/"

void AudioManager::playOnVariableVolumeWithId(int id, double dist){
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (!(it != this->audiotracks.end())) {
    std::cerr << TRACK_NOT_FOUND_ERROR << id << std::endl;
    return;
  }
  Audio* audio = it->second;
  audio->volumeDownWithDist(dist);
  audio->play();
}

AudioManager::~AudioManager() {
  this->garbageCollector();
}

bool AudioManager::loadAndCheckTrack(int i, const std::string& name) {
  Audio* audio = new Audio((AUDIO_PATH + name).c_str(), !IS_MUSIC);
  if (audio == NULL) {
    return false;
  }
  this->loadTrack(i, audio);
  return true;
}

AudioManager::AudioManager() {
  std::vector<std::string> names({ "Knife.wav", // 1
                                   "Pistol.wav", // 2
                                   "Machine Gun.wav", // 3
                                   "Gatling Gun.wav", //4
                                   "Door.wav", // 5
                                   "ItemPickup.wav" // 6
                                  });
  int i = 1;
  for (std::string& name : names) {
    if (!this->loadAndCheckTrack(i,name)){
      this->garbageCollector();
      throw SdlException(TRACK_NOT_FOUND_ERROR, Mix_GetError());
      break;
    }
    i++;
  }
}

void AudioManager::stopWithId(int id) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end())
    it->second->stop();
  else
    std::cerr << TRACK_NOT_FOUND_ERROR << id << std::endl;
}

void AudioManager::loadTrack(int id, Audio* audio) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end())
    std::cerr << TRACK_NOT_FOUND_ERROR << id << std::endl;
  else
    this->audiotracks[id] = audio;
}

void AudioManager::playWithId(int id) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end())
    it->second->play();
  else
    std::cerr << TRACK_NOT_FOUND_ERROR << id << std::endl;
}

void AudioManager::playOnMaxVolumeWithId(int id) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end())
    it->second->playWithMaxVolume();
  else
    std::cerr << TRACK_NOT_FOUND_ERROR << id << std::endl;
}

void AudioManager::garbageCollector() {
  std::map<int, Audio*>::iterator it = this->audiotracks.begin();
  for (; it != this->audiotracks.end(); ++it) {
    delete it->second;
  }
}
