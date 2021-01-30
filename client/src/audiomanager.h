#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <map>
#include "audio.h"

class AudioManager {
 public:
  ~AudioManager();
  AudioManager();
  void playWithId(int id);
  void playOnMaxVolumeWithId(int id);
  void playOnVariableVolumeWithId(int id, double distance);
  void playOrStopOnVariableVolumeWithId(int id, double distance);
  void stopWithId(int id);
  void loadTrack(int id, Audio* audio);
  bool loadAndCheckTrack(int id, Audio* audio);
 private:
  bool loadAndCheckTrack(int i, const std::string& name);
  void garbageCollector();
  std::map<int,Audio*> audiotracks;
};

#endif  // AUDIOMANAGER_H_
