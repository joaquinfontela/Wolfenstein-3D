#include "audio.h"
#include "sdlexception.h"
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>

#define AUDIO_PATH "../audio/"
#define TIMES_THE_AUDIO_IS_PLAYED 1

Audio::~Audio() {
  Mix_FreeMusic(this->audio);
}

void Audio::playOrStopAudio(){
  if (!Mix_PlayingMusic())
    Mix_PlayMusic(this->audio, TIMES_THE_AUDIO_IS_PLAYED);
  else if (Mix_PausedMusic())
    Mix_ResumeMusic();
  else
    Mix_PauseMusic();
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
