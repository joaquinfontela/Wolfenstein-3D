#ifndef NULL_PTR_QUEUE_H
#define NULL_PTR_QUEUE_H

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

#endif
