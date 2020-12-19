#ifndef WAITING_QUEUE_H
#define WAITING_QUEUE_H

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

template <class T>
class WaitingQueue {
 private:
  std::queue<T> q;
  std::mutex m;
  std::condition_variable accessManager;
  bool shutdown = false;

 public:
  WaitingQueue();
  ~WaitingQueue();

  void push(T element);
  T pop();
  T front();
  bool isEmpty();

  void requestShutdown(){
    {
      std::unique_lock<std::mutex> lock(m);
      this->shutdown = true;
    }

    accessManager.notify_all();
  }
};

template <class T>
WaitingQueue<T>::WaitingQueue() {}

template <class T>
WaitingQueue<T>::~WaitingQueue() {}

template <class T>
void WaitingQueue<T>::push(T element) {
  std::unique_lock<std::mutex> lock(m);
  q.push(element);
  accessManager.notify_one();
}

template <class T>
T WaitingQueue<T>::pop() {
  std::unique_lock<std::mutex> lock(m);
  while (q.empty()){
    accessManager.wait(lock);
    if(shutdown)
      return nullptr;
  }
  T elementToReturn = q.front();
  q.pop();
  return elementToReturn;
}

template <class T>
T WaitingQueue<T>::front() {
  std::unique_lock<std::mutex> lock(m);
  if (q.empty()) return nullptr;
  return q.front();
}

template <class T>
bool WaitingQueue<T>::isEmpty() {
  std::unique_lock<std::mutex> lock(m);
  return q.empty();
}

#endif
