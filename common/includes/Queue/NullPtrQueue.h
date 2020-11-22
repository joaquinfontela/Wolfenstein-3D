#include <iostream>
#include <mutex>
#include <queue>

template <class T>
class NullPtrQueue {
 private:
  std::queue<T> q;
  std::mutex m;

 public:
  NullPtrQueue();
  ~NullPtrQueue();

  void push(T element);
  T pop();
  T front();
  bool isEmpty();
};

template <class T>
NullPtrQueue<T>::NullPtrQueue() {}

template <class T>
NullPtrQueue<T>::~NullPtrQueue() {}

template <class T>
void NullPtrQueue<T>::push(T element) {
  std::unique_lock<std::mutex> lock(m);
  q.push(element);
}

template <class T>
T NullPtrQueue<T>::pop() {
  std::unique_lock<std::mutex> lock(m);
  if (q.empty()) {
    return nullptr;
  }
  T elementToReturn = q.front();
  q.pop();
  return elementToReturn;
}

template <class T>
T NullPtrQueue<T>::front() {
  return q.front();
}

template <class T>
bool NullPtrQueue<T>::isEmpty() {
  return q.empty();
}

template <>
class NullPtrQueue<void*> {
 private:
  std::queue<void*> q;
  std::mutex m;

 public:
  void push(void* element);
  void* pop();
  void* front();
  bool isEmpty();
};

void NullPtrQueue<void*>::push(void* element) {
  std::unique_lock<std::mutex> lock(m);
  q.push(element);
}

void* NullPtrQueue<void*>::pop() {
  std::unique_lock<std::mutex> lock(m);
  if (q.empty()) {
    return nullptr;
  }
  void* elementToReturn = q.front();
  q.pop();
  return elementToReturn;
}

void* NullPtrQueue<void*>::front() { return q.front(); }

bool NullPtrQueue<void*>::isEmpty() { return q.empty(); }

template <class T>
class NullPtrQueue<T*> : private NullPtrQueue<void*> {
 public:
  void push(T* element);
  T* pop();
  T* front();
  bool isEmpty();
};

template <class T>
void NullPtrQueue<T*>::push(T* element) {
  NullPtrQueue<void*>::push(element);
}

template <class T>
T* NullPtrQueue<T*>::pop() {
  return (T*)NullPtrQueue<void*>::pop();
}

template <class T>
T* NullPtrQueue<T*>::front() {
  return (T*)NullPtrQueue<void*>::front();
}

template <class T>
bool NullPtrQueue<T*>::isEmpty() {
  return (T*)NullPtrQueue<void*>::isEmpty();
}