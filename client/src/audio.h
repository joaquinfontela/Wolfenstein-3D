#ifndef AUDIO_H_
#define AUDIO_H_

#include <SDL2/SDL_mixer.h>

#include <string>

#include "clientprotocol.h"

/**
 * @brief This union comes in handy due to the fact that each instance
 * of this class is either music or an audio chunk, and since both are pointers
 * I can put them on this structure and dedice how to cast depending on some
 * boolean value.
 *
 */
union Sound {
  Mix_Music* music;
  Mix_Chunk* chunk;
};

class Audio {
 private:
  int channel;
  union Sound audio;
  bool isMusic;
  int volume;

 public:
  /**
   * @brief Lowers the audio depending on the distance of the entity that
   * emitted the sound.
   *
   * @param dist Distance from the sound emitting entity.
   */
  void volumeDownWithDist(double dist);

  /**
   * @brief Turns up the volume.
   *
   */
  void volumeUp();

  /**
   * @brief Construct a new Audio object.
   *
   * @param name Name of the audio file to load.
   * @param isMusic True if it's background music, false in any other case.
   * @param volume Starting volume.
   */
  Audio(const char* name, bool isMusic, int volume = 30);

  /**
   * @brief Destroy the Audio object.
   *
   */
  ~Audio();

  /**
   * @brief PLays audio.
   *
   */
  void play();

  /**
   * @brief Stops the music from playing.
   *
   */
  void stop();

  /**
   * @brief Plays sonund with max volume.
   *
   */
  void playWithMaxVolume();
};

#endif  // AUDIO_H_
