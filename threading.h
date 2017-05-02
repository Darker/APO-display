#ifndef THREADING_H
#define THREADING_H
// included because it magically
// defines _GLIBCXX_HAS_GTHREADS
#include <string>
#ifdef _GLIBCXX_HAS_GTHREADS
#include <mutex>
#include <thread>
#else

#warning "Including fake mutex headers!"
#include "libs/mingw.mutex.h"
#ifdef _GLIBCXX_HAS_GTHREADS
#warning "_GLIBCXX_HAS_GTHREADS constant magically appeared 2"
#endif
#include "libs/mingw.thread.h"
#define _GLIBCXX_MUTEX 1
#endif

#endif // THREADING_H
