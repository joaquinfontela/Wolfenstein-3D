#include "audio.h"
#include "sdlexception.h"
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include <math.h>

#define AUDIO_PATH "../audio/"
#define TIMES_THE_AUDIO_IS_PLAYED 1

Audio::~Audio() {
  Mix_FreeMusic(this->audio);
}

void Audio::volumeDownWithDist(double dist) {
  this->volume = floor(17.0/(log(dist)));
  std::cout << "dist: " << dist << " vol: " << this->volume << std::endl;
  Mix_VolumeMusic(this->volume); // Máx 128.
}

void Audio::playOrStopAudio(){
  if (!Mix_PlayingMusic())
    Mix_PlayMusic(this->audio, TIMES_THE_AUDIO_IS_PLAYED);
  else if (Mix_PausedMusic())
    Mix_ResumeMusic();
  else
    Mix_PauseMusic();
}

void Audio::playOrStopAudioWithMaxVolume() {
  Mix_VolumeMusic(MIX_MAX_VOLUME);
  this->playOrStopAudio();
  Mix_VolumeMusic(this->volume);
}

void Audio::volumeUp() {
  std::cout << "disparando con vol: " << this->volume << std::endl;
  Mix_VolumeMusic(this->volume); // Máx 128.
  this->volume += 3;
}

Audio::Audio(const char* name) : volume(30) {
  if (!(this->audio = Mix_LoadMUS(name))) {
    throw SdlException(Mix_GetError());
  }
}
