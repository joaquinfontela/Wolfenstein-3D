#ifndef LOG_H_
#define LOG_H_

#include <mutex>

/**
 * @brief Logs non-fatal errors to "wolfenstein.log".
 *
 */
class Log {
 public:
  /**
   * @brief Logs an error message.
   *
   * @param _file Caller function.
   * @param function Caller function.
   * @param line Caller line.
   * @param msg Log message to write.
   */
  void static log(const char* _file, const char* function, const int line,
                   const char* msg);
  static int playerId;
  static std::mutex lock;
};

#endif  // LOG_H_
