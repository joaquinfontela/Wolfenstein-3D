#ifndef LOG_H_
#define LOG_H_

#include <mutex>

class Log {
 public:
  void static test(const char* _file, const char* function, const int line, const char* msg);
  static int playerId;
};

#endif  // LOG_H_
