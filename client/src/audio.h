#ifndef AUDIO_H_
#define AUDIO_H_

#include <SDL2/SDL_mixer.h>

#include <string>

#include "clientprotocol.h"
#include "sound.h"

/**
 * @brief Encapsulates the behaviour and data regarding the audio.
 *
 */
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
