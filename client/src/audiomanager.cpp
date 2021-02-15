#include "../includes/audiomanager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "../includes/clientprotocol.h"
#include "../includes/sdlexception.h"

#define TRACK_INIT_ERROR "Error, track already found: "
#define TRACK_FOUND_ERROR "Error, track found with code: "
#define TRACK_NOT_FOUND_ERROR "Error, track not found with code: "
#define AUDIO_PATH "../audio/"

void AudioManager::playOnVariableVolumeWithId(int id, double dist) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (!(it != this->audiotracks.end())) {
    LOG_WITH_ID(TRACK_NOT_FOUND_ERROR);
    return;
  }
  Audio* audio = it->second;
  audio->volumeDownWithDist(dist);
  audio->play();
}

void AudioManager::playOrStopOnVariableVolumeWithId(int id, double dist) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (!(it != this->audiotracks.end())) {
    LOG_WITH_ID(TRACK_NOT_FOUND_ERROR);
    return;
  }
  Audio* audio = it->second;
  audio->volumeDownWithDist(dist);
  audio->play();
}

AudioManager::~AudioManager() { this->garbageCollector(); }

bool AudioManager::loadAndCheckTrack(int i, const std::string& name) {
  Audio* audio;
  if (i == MUSIC) {
    audio = new Audio((AUDIO_PATH + name).c_str(),  IS_MUSIC, MUSIC_VOLUME);
  } else if (i == DOOR_SOUND) {
    audio = new Audio((AUDIO_PATH + name).c_str(), !IS_MUSIC, DOOR_VOLUME);
  } else if (IS_GUN_SOUND(i)) {
    audio = new Audio((AUDIO_PATH + name).c_str(), !IS_MUSIC, SHOOTING_VOLUME);
  } else {
    audio = new Audio((AUDIO_PATH + name).c_str(), !IS_MUSIC);
  }
  if (audio == NULL || !this->loadTrack(i, audio)) {
    delete audio;
    return false;
  }
  return true;
}

AudioManager::AudioManager() {
  std::vector<std::string> names({
      "Knife.wav",            // 1
      "Pistol.wav",           // 2
      "Machine Gun.wav",      // 3
      "Gatling Gun.wav",      // 4
      "Rocket Launcher.wav",  // 5
      "Rocket Explode.wav",   // 6
      "Door.wav",             // 7
      "ItemPickup.wav",       // 8
      "HealthPickup.wav",     // 9
      "Dog Death.wav",        // 10
      "Death 1.wav",          // 11
      "Death 2.wav",          // 12
      "Player Pain 2.wav",    // 13
      "Enemy Pain.wav",       // 14
      "music.mp3",            // 15
      "Secret Entrance.wav"   // 16
  });
  int i = 1;
  for (std::string& name : names) {
    if (!this->loadAndCheckTrack(i, name)) {
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
    LOG_WITH_ID(TRACK_NOT_FOUND_ERROR);
}

bool AudioManager::loadTrack(int id, Audio* audio) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end()) {
    LOG_WITH_ID(TRACK_FOUND_ERROR);
    return false;
  }
  this->audiotracks[id] = audio;
  return true;
}

void AudioManager::playWithId(int id) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end())
    it->second->play();
  else
    LOG_WITH_ID(TRACK_NOT_FOUND_ERROR);
}

void AudioManager::playOnMaxVolumeWithId(int id) {
  std::map<int, Audio*>::iterator it = this->audiotracks.find(id);
  if (it != this->audiotracks.end())
    it->second->playWithMaxVolume();
  else
    LOG_WITH_ID(TRACK_NOT_FOUND_ERROR);
}

void AudioManager::garbageCollector() {
  std::map<int, Audio*>::iterator it = this->audiotracks.begin();
  for (; it != this->audiotracks.end(); ++it) {
    delete it->second;
  }
}
