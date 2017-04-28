#ifndef THREADING_H
#define THREADING_H
#ifdef _GLIBCXX_HAS_GTHREADS
#include <mutex>
#include <thread>
#else
#include "libs/mingw.mutex.h"
#include "libs/mingw.thread.h"
#define _GLIBCXX_MUTEX 1
#endif

#endif // THREADING_H
