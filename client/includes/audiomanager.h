#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <map>
#include <vector>
#include <string>

#include "audio.h"

/**
 * @brief Class used to organize the audio files and stop duplicates from
 * existing.
 *
 */
class AudioManager {
 public:
  /**
   * @brief Calls the garbage collector.
   *
   */
  ~AudioManager();

  /**
   * @brief Construct a new Audio Manager object, initializing every audio
   * instance. Throws an Exception if the process fails.
   *
   */
  AudioManager();

  /**
   * @brief Plays the choosen audio track. Throws an Exception if it fails.
   *
   * @param id Id of the sound to be played. Key of the sounds dict.
   */
  void playWithId(int id);

  /**
   * @brief Plays the choosen audio track on max volume. Throws an Exception if
   * it fails.
   *
   * @param id Id of the sound to be played. Key of the sounds dict.
   */
  void playOnMaxVolumeWithId(int id);

  /**
   * @brief Plays the choosen audio track on variable volume. The greater the
   * distance from the sound emitting entity, the lower the volume. Throws an
   * Exception if it fails.
   *
   * @param id Id of the sound to be played. Key of the sounds dict.
   */
  void playOnVariableVolumeWithId(int id, double distance);

  /**
   * @brief Plays or stops the choosen audio track on variable volume. The
   * greater the distance from the sound emitting entity, the lower the volume.
   * Throws an Exception if it fails.
   *
   * @param id Id of the sound to be played. Key of the sounds dict.
   */
  void playOrStopOnVariableVolumeWithId(int id, double distance);

  /**
   * @brief Stops the choosen audio track. Throws an Exception if it fails.
   *
   * @param id Id of the sound to be played. Key of the sounds dict.
   */
  void stopWithId(int id);

 private:
  /**
   * @brief Creates the audio track from the name given and stores it on the
   * audio dictionary. If it fails it deallocates the resources and returns
   * false.
   *
   * @param i Audio track id.
   * @param name Audio track file name.
   * @return true When no errors arise.
   * @return false If the audio file couldn't be loaded or if it's stepping on
   * another id.
   */
  bool loadAndCheckTrack(int i, const std::string& name);

  /**
   * @brief Loads the audio track onto the audio track dictionary.
   *
   * @param id Audio track id.
   * @param audio Audio reference
   * @return true when the operation is successful operation.
   * @return false if there is another audio track loaded with the same id.
   */
  bool loadTrack(int id, Audio* audio);

  /**
   *
   * @brief Deletes all the audio files created on init.
   *
   */
  void garbageCollector();
  std::map<int, Audio*> audiotracks;
};

#endif  // AUDIOMANAGER_H_
