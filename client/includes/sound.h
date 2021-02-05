#ifndef SOUND_H_
#define SOUND_H_

#include <SDL2/SDL_mixer.h>
/**
 * @brief This union comes in handy due to the fact that each instance
 * of this class is either music or an audio chunk, and since both are pointers
 * I can put them on this structure and decide how to cast depending on some
 * boolean value.
 *
 */
union Sound {
  Mix_Music* music;
  Mix_Chunk* chunk;
};

#endif  // SOUND_H_