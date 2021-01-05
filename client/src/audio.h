#ifndef AUDIO_H_
#define AUDIO_H_

#include <string>
#include <SDL2/SDL_mixer.h>

class Audio {
 private:
  Mix_Music* audio;
  int volume;
 public:
  void volumeUp();
  Audio(std::string& name);
  ~Audio();
  void playOrStopAudio();
};

#endif  // AUDIO_H_
