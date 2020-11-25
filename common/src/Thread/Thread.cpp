#include "../../includes/Thread/Thread.h"

#include <thread>
#include <utility>

Thread::Thread() {}

void Thread::start() { this->thread = std::thread(&Thread::run, this); }

void Thread::join() { thread.join(); }

Thread::Thread(Thread&& other) { this->thread = std::move(other.thread); }
