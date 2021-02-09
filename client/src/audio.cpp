#include "../includes/audio.h"

#include <SDL2/SDL_mixer.h>
#include <math.h>

#include <iostream>
#include <string>

#include "../includes/clientprotocol.h"
#include "../includes/sdlexception.h"

Audio::~Audio() {
  if (isMusic)
    Mix_FreeMusic(this->audio.music);
  else
    Mix_FreeChunk(this->audio.chunk);
}

void Audio::volumeDownWithDist(double dist) {
  this->volume = floor(17.0 / (log(dist)));
  if (isMusic)
    Mix_VolumeMusic(this->volume);  // Máx 128.
  else
    Mix_VolumeChunk(this->audio.chunk, this->volume);  // Máx 128.
}

void Audio::play() {
  // if (!Mix_PlayingMusic())
  if (isMusic) {
    Mix_PlayMusic(this->audio.music, TIMES_THE_AUDIO_IS_PLAYED);
  } else {
    Mix_Pause(-1);
    this->channel = Mix_PlayChannel(-1, this->audio.chunk, 0);
    Mix_Resume(-1);
    // else if (Mix_PausedMusic())
    //  Mix_ResumeMusic();
  }
}

void Audio::playWithMaxVolume() {
  if (isMusic) {
    Mix_VolumeMusic(MIX_MAX_VOLUME);
    this->play();
    Mix_VolumeMusic(this->volume);
  } else {
    Mix_VolumeChunk(this->audio.chunk, MIX_MAX_VOLUME);
    this->play();
    Mix_VolumeChunk(this->audio.chunk, this->volume);
  }
}

void Audio::stop() {
  if (!Mix_PlayingMusic()) Mix_PauseMusic();
}

void Audio::volumeUp() {
  this->volume += 3;
  if (isMusic)
    Mix_VolumeMusic(this->volume);  // Máx 128.
  else
    Mix_VolumeChunk(this->audio.chunk, this->volume);  // Máx 128.
}

Audio::Audio(const char* name, bool isMusic, int volume)
    : isMusic(isMusic), volume(volume), channel(ERROR) {
  memset(&this->audio, 0, sizeof(this->audio));
  if (isMusic) {
    Mix_VolumeMusic(this->volume);  // Máx 128.
    if (!(this->audio.music = Mix_LoadMUS(name))) {
      throw SdlException(Mix_GetError());
    }
    Mix_VolumeChunk(this->audio.chunk, this->volume);
  } else if (!(this->audio.chunk = Mix_LoadWAV(name))) {
    throw SdlException(Mix_GetError());
  }
}
