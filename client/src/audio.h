#ifndef AUDIO_H_
#define AUDIO_H_

#include <string>
#include <SDL2/SDL_mixer.h>

union Sound {
  Mix_Music* music;
  Mix_Chunk* chunk;
};

class Audio {
 private:
  union Sound audio;
  bool isMusic;
  int volume;
 public:
  void volumeDownWithDist(double dist);
  void volumeUp();
  Audio(const char* name, bool isMusic);
  ~Audio();
  void play();
  void stop();
  void playWithMaxVolume();
};

#endif  // AUDIO_H_
