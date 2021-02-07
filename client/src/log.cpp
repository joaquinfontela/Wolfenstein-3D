#include "../includes/log.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>

#define LOG_FILE_NAME "wolfenstein.log"

int Log::playerId = -1;
std::mutex Log::lock;

void Log::log(const char* _file, const char* function, const int line,
               const char* msg) {
  std::unique_lock<std::mutex> lock(Log::lock);
  std::string file = std::string(_file);
  file = file.substr(file.find("/src/") + 5);
  std::time_t time =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  std::ofstream logfile;
  logfile.open(LOG_FILE_NAME, std::ios::app);
  logfile << std::put_time(localtime(&time), "%T") << " [PLAYER "
          << Log::playerId << "] File: " << file << " - Function: " << function
          << " - Line: " << line << " " << msg << std::endl;
  logfile.close();
}
