#ifndef AUDIO_H_
#define AUDIO_H_

#include <string>
#include <SDL2/SDL_mixer.h>

class Audio {
 private:
  Mix_Music* audio;
  int volume;
 public:
  void volumeDownWithDist(double dist);
  void volumeUp();
  Audio(const char* name);
  ~Audio();
  void play();
  void stop();
  void playWithMaxVolume();
};

#endif  // AUDIO_H_
