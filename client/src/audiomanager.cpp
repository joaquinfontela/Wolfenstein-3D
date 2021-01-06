#include "sdlexception.h"
#include "audiomanager.h"
#include <vector>
#include <string>
#include <iostream>

#define TRACK_INIT_ERROR "Error, track already found: "
#define TRACK_NOT_FOUND_ERROR "Error, track not found with code: "
#define AUDIO_PATH "../audio/"

void AudioManager::playOrStopAudioOnVariableVolumeWithId(int id, double dist){
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (!(it != this->audiotracks.end())) {
    std::cerr << TRACK_NOT_FOUND_ERROR << id << std::endl;
    return;
  }
  Audio* audio = it->second;
  audio->volumeDownWithDist(dist);
  audio->playOrStopAudio();
}

AudioManager::~AudioManager() {
  this->garbageCollector();
}

bool AudioManager::loadAndCheckTrack(int i, const std::string& name) {
  Audio* audio = new Audio((AUDIO_PATH + name).c_str());
  if (audio == NULL) {
    return false;
  }
  this->loadTrack(i, audio);
  return true;
}

AudioManager::AudioManager() {
  std::vector<std::string> names({ "song.mp3", // 1
                                   "Pistol.wav", // 2
                                   "Machine Gun.wav" // 3
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

void AudioManager::loadTrack(int id, Audio* audio) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end())
    std::cerr << TRACK_NOT_FOUND_ERROR << id << std::endl;
  else
    this->audiotracks[id] = audio;
}

void AudioManager::playOrStopWithId(int id) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end())
    it->second->playOrStopAudio();
  else
    std::cerr << TRACK_NOT_FOUND_ERROR << id << std::endl;
}

void AudioManager::playOrStopAudioOnMaxVolumeWithId(int id) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end())
    it->second->playOrStopAudioWithMaxVolume();
  else
    std::cerr << TRACK_NOT_FOUND_ERROR << id << std::endl;
}

void AudioManager::garbageCollector() {
  std::map<int, Audio*>::iterator it = this->audiotracks.begin();
  for (; it != this->audiotracks.end(); ++it) {
    delete it->second;
  }
}
