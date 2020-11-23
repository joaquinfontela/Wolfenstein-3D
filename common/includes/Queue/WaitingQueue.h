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

 public:
  WaitingQueue();
  ~WaitingQueue();

  void push(T element);
  T pop();
  T front();
  bool isEmpty();
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
  while (q.empty()) accessManager.wait(lock);
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

// _______________________________________________

template <>
class WaitingQueue<void*> {
 private:
  std::queue<void*> q;
  std::mutex m;
  std::condition_variable accessManager;

 public:
  void push(void* element);
  void* pop();
  void* front();
  bool isEmpty();
};

void WaitingQueue<void*>::push(void* element) {
  std::unique_lock<std::mutex> lock(m);
  q.push(element);
  accessManager.notify_one();
}

void* WaitingQueue<void*>::pop() {
  std::unique_lock<std::mutex> lock(m);
  while (q.empty()) accessManager.wait(lock);
  void* elementToReturn = q.front();
  q.pop();
  return elementToReturn;
}

void* WaitingQueue<void*>::front() {
  std::unique_lock<std::mutex> lock(m);
  if (q.empty()) return nullptr;
  return q.front();
}

bool WaitingQueue<void*>::isEmpty() {
  std::unique_lock<std::mutex> lock(m);
  return q.empty();
}

//____________________________________

template <class T>
class WaitingQueue<T*> : private WaitingQueue<void*> {
 public:
  void push(T* element);
  T* pop();
  T* front();
  bool isEmpty();
};

template <class T>
void WaitingQueue<T*>::push(T* element) {
  WaitingQueue<void*>::push(element);
}

template <class T>
T* WaitingQueue<T*>::pop() {
  return (T*)WaitingQueue<void*>::pop();
}

template <class T>
T* WaitingQueue<T*>::front() {
  return (T*)WaitingQueue<void*>::front();
}

template <class T>
bool WaitingQueue<T*>::isEmpty() {
  return (T*)WaitingQueue<void*>::isEmpty();
}
