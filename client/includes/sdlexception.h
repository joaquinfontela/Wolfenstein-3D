#ifndef __SDL_EXCEPTION_H__
#define __SDL_EXCEPTION_H__
#include <exception>
#include <string>

#define ERROR_SDL "\nSDL ERROR: "

/**
 * @brief Exception class to throw SDL errors.
 *
 */
class SdlException : public std::exception {
 public:
  /**
   * @brief Construct a new Sdl Exception object
   *
   * @param description Error description.
   * @param sdlError Sdl error description.
   */
  SdlException(const char* description, const char* sdlError);

  /**
   * @brief Construct a new Sdl Exception object
   *
   * @param sdlError Sdl error description.
   */
  SdlException(const char* sdlError);
  const char* what() const noexcept;

 private:
  std::string description = ERROR_SDL;
};

#endif
