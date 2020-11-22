#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>
#include <utility>

class Thread {
 private:
  std::thread thread;

 public:
  Thread();

  // Inicia el thread
  void start();

  // Hace join del thread
  void join();

  // funcion a implementar por clases herederas, es la ejecucion del thread.
  virtual void run() = 0;
  virtual ~Thread() {}
  Thread(const Thread& other) = delete;
  Thread& operator=(const Thread&) = delete;
  Thread(Thread&& other);
  Thread& operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
  }
};

#endif