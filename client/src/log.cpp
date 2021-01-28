#include "log.h"

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <mutex>

#define LOG_FILE_NAME "wolfenstein.log"

void Log::test(const char* _file, const char* function, const int line, const char* msg) {
  static std::mutex mutex;

  std::lock_guard<std::mutex> lock(mutex);
  std::string file = std::string(_file);
  file = file.substr(file.find("/src/"));
  std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  std::ofstream logfile;
  logfile.open(LOG_FILE_NAME, std::ios::app);
  logfile << std::put_time(localtime(&time), "%T") << " [CLIENT] File: " << file
  << " - Function: " << function << " - Line: " << line << " " << msg << std::endl;
  logfile.close();
}
