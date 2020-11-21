#ifndef SDLEXCEPTION_H_
#define SDLEXCEPTION_H_
#include <exception>
#include <string>

#define ERROR_SDL "\nSDL ERROR: "

class SdlException : public std::exception {
 public:
  SdlException(const char* description, const char* sdlError);
  const char* what() const noexcept;

 private:
  std::string description = ERROR_SDL;
};

#endif  // SDLEXCEPTION_H_
