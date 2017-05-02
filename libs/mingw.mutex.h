/**
* @file mingw.mutex.h
* @brief std::mutex et al implementation for MinGW
** (c) 2013-2016 by Mega Limited, Auckland, New Zealand
* @author Alexander Vassilev
*
* @copyright Simplified (2-clause) BSD License.
* You should have received a copy of the license along with this
* program.
*
* This code is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* @note
* This file may become part of the mingw-w64 runtime package. If/when this happens,
* the appropriate license will be added, i.e. this code will become dual-licensed,
* and the current BSD 2-clause license will stay.
*/

#ifndef WIN32STDMUTEX_H
#define WIN32STDMUTEX_H
#ifdef _GLIBCXX_HAS_GTHREADS
#error This version of MinGW seems to include a win32 port of pthreads, and probably    \
    already has C++11 std threading classes implemented, based on pthreads.             \
    You are likely to have class redefinition errors below, and unfirtunately this      \
    implementation can not be used standalone                                           \
    and independent of the system <mutex> header, since it relies on it for             \
    std::unique_lock and other utility classes. If you would still like to use this     \
    implementation (as it is more lightweight), you have to edit the                    \
    c++-config.h system header of your MinGW to not define _GLIBCXX_HAS_GTHREADS.       \
    This will prevent system headers from defining actual threading classes while still \
    defining the necessary utility classes.
#endif
// Recursion checks on non-recursive locks have some performance penalty, so the user
// may want to disable the checks in release builds. In that case, make sure they
// are always enabled in debug builds.

#if defined(STDMUTEX_NO_RECURSION_CHECKS) && !defined(NDEBUG)
    #undef STDMUTEX_NO_RECURSION_CHECKS
#endif

#include <windows.h>
#include <chrono>
#include <system_error>
#include <cstdio>

#ifndef EPROTO
    #define EPROTO 134
#endif
#ifndef EOWNERDEAD
    #define EOWNERDEAD 133
#endif

namespace std
{
class recursive_mutex
{
protected:
    CRITICAL_SECTION mHandle;
public:
    typedef LPCRITICAL_SECTION native_handle_type;
    native_handle_type native_handle() {return &mHandle;}
    recursive_mutex() noexcept
    {
        InitializeCriticalSection(&mHandle);
    }
    recursive_mutex (const recursive_mutex&) = delete;
    recursive_mutex& operator=(const recursive_mutex&) = delete;
    ~recursive_mutex() noexcept
    {
        DeleteCriticalSection(&mHandle);
    }
    void lock()
    {
        EnterCriticalSection(&mHandle);
    }
    void unlock()
    {
        LeaveCriticalSection(&mHandle);
    }
    bool try_lock()
    {
        return (TryEnterCriticalSection(&mHandle)!=0);
    }
};
template <class B>
class _NonRecursive: protected B
{
protected:
    typedef B base;
    DWORD mOwnerThread;
public:
    using typename base::native_handle_type;
    using base::native_handle;
    _NonRecursive() noexcept :base(), mOwnerThread(0) {}
    _NonRecursive (const _NonRecursive<B>&) = delete;
    _NonRecursive& operator= (const _NonRecursive<B>&) = delete;
    void lock()
    {
        base::lock();
        checkSetOwnerAfterLock();
    }
protected:
    void checkSetOwnerAfterLock()
    {
        DWORD self = GetCurrentThreadId();
//        if (mOwnerThread == self)
//        {
//            std::fprintf(stderr, "FATAL: Recursive locking of non-recursive mutex detected. Throwing system exception\n");
//            std::fflush(stderr);
//            throw std::system_error(EDEADLK, std::generic_category());
//        }
        mOwnerThread = self;
    }
    void checkSetOwnerBeforeUnlock()
    {
//        DWORD self = GetCurrentThreadId();
//        if (mOwnerThread != self)
//        {
//            std::fprintf(stderr, "FATAL: Recursive unlocking of non-recursive mutex detected. Throwing system exception\n");
//            std::fflush(stderr);
//            throw std::system_error(EDEADLK, std::generic_category());
//        }
        mOwnerThread = 0;
    }
public:
    void unlock()
    {
        checkSetOwnerBeforeUnlock();
        base::unlock();
    }
    bool try_lock()
    {
        bool ret = base::try_lock();
        if (ret)
            checkSetOwnerAfterLock();
        return ret;
    }
};

#ifndef STDMUTEX_NO_RECURSION_CHECKS
    typedef _NonRecursive<recursive_mutex> mutex;
#else
    typedef recursive_mutex mutex;
#endif

class recursive_timed_mutex
{
protected:
    HANDLE mHandle;
public:
    typedef HANDLE native_handle_type;
    native_handle_type native_handle() const {return mHandle;}
    recursive_timed_mutex(const recursive_timed_mutex&) = delete;
    recursive_timed_mutex& operator=(const recursive_timed_mutex&) = delete;
    recursive_timed_mutex(): mHandle(CreateMutex(NULL, FALSE, NULL)){}
    ~recursive_timed_mutex()
    {
        CloseHandle(mHandle);
    }
    void lock()
    {
        DWORD ret = WaitForSingleObject(mHandle, INFINITE);
        if (ret != WAIT_OBJECT_0)
        {
            if (ret == WAIT_ABANDONED)
                throw std::system_error(EOWNERDEAD, std::generic_category());
            else
                throw std::system_error(EPROTO, std::generic_category());
        }
    }
    void unlock()
    {
        if (!ReleaseMutex(mHandle))
            throw std::system_error(EDEADLK, std::generic_category());
    }
    bool try_lock()
    {
        DWORD ret = WaitForSingleObject(mHandle, 0);
        if (ret == WAIT_TIMEOUT)
            return false;
        else if (ret == WAIT_OBJECT_0)
            return true;
        else if (ret == WAIT_ABANDONED)
            throw std::system_error(EOWNERDEAD, std::generic_category());
        else
            throw std::system_error(EPROTO, std::generic_category());
    }
    template <class Rep, class Period>
    bool try_lock_for(const std::chrono::duration<Rep,Period>& dur)
    {
        DWORD timeout = (DWORD)std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

        DWORD ret = WaitForSingleObject(mHandle, timeout);
        if (ret == WAIT_TIMEOUT)
            return false;
        else if (ret == WAIT_OBJECT_0)
            return true;
        else if (ret == WAIT_ABANDONED)
            throw std::system_error(EOWNERDEAD, std::generic_category());
        else
            throw std::system_error(EPROTO, std::generic_category());
    }
    template <class Clock, class Duration>
    bool try_lock_until(const std::chrono::time_point<Clock,Duration>& timeout_time)
    {
        return try_lock_for(timeout_time - Clock::now());
    }
};

class timed_mutex: public _NonRecursive<recursive_timed_mutex>
{
protected:
    typedef _NonRecursive<recursive_timed_mutex> base;
public:
    using base::base;
    timed_mutex(const timed_mutex&) = delete;
    timed_mutex& operator=(const timed_mutex&) = delete;
    template <class Rep, class Period>
    bool try_lock_for(const std::chrono::duration<Rep,Period>& dur)
    {
        bool ret = base::try_lock_for(dur);
#ifndef STDMUTEX_NO_RECURSION_CHECKS
        if (ret)
            checkSetOwnerAfterLock();
#endif
        return ret;
    }
public:
    template <class Clock, class Duration>
    bool try_lock_until(const std::chrono::time_point<Clock,Duration>& timeout_time)
    {
        bool ret = base::try_lock_until(timeout_time);
#ifndef STDMUTEX_NO_RECURSION_CHECKS
        if (ret)
            checkSetOwnerAfterLock();
#endif
        return ret;
    }
};
// You can use the scoped locks and other helpers that are still provided by <mutex>
// In that case, you must include <mutex> before including this file, so that this
// file will not try to redefine them
#ifndef _GLIBCXX_MUTEX

/// Do not acquire ownership of the mutex.
struct defer_lock_t { };

 /// Try to acquire ownership of the mutex without blocking.
struct try_to_lock_t { };

 /// Assume the calling thread has already obtained mutex ownership
 /// and manage it.
struct adopt_lock_t { };

constexpr defer_lock_t	defer_lock { };
constexpr try_to_lock_t	try_to_lock { };
constexpr adopt_lock_t	adopt_lock { };

template <class M>
class lock_guard
{
protected:
    M& mMutex;
public:
    typedef M mutex_type;
    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;
    explicit lock_guard(mutex_type& m): mMutex(m) { mMutex.lock();  }
    lock_guard(mutex_type& m, adopt_lock_t):mMutex(m){}
    ~lock_guard() {  mMutex.unlock();   }
};

#endif

// copied from std <mutex> header
/// unique_lock
template<typename _Mutex>
  class unique_lock
  {
  public:
    typedef _Mutex mutex_type;

    unique_lock() noexcept
    : _M_device(0), _M_owns(false)
    { }

    explicit unique_lock(mutex_type& __m)
    : _M_device(&__m), _M_owns(false)
    {
  lock();
  _M_owns = true;
    }

    unique_lock(mutex_type& __m, defer_lock_t) noexcept
    : _M_device(&__m), _M_owns(false)
    { }

    unique_lock(mutex_type& __m, try_to_lock_t)
    : _M_device(&__m), _M_owns(_M_device->try_lock())
    { }

    unique_lock(mutex_type& __m, adopt_lock_t)
    : _M_device(&__m), _M_owns(true)
    {
  // XXX calling thread owns mutex
    }

    template<typename _Clock, typename _Duration>
  unique_lock(mutex_type& __m,
          const chrono::time_point<_Clock, _Duration>& __atime)
  : _M_device(&__m), _M_owns(_M_device->try_lock_until(__atime))
  { }

    template<typename _Rep, typename _Period>
  unique_lock(mutex_type& __m,
          const chrono::duration<_Rep, _Period>& __rtime)
  : _M_device(&__m), _M_owns(_M_device->try_lock_for(__rtime))
  { }

    ~unique_lock()
    {
  if (_M_owns)
    unlock();
    }

    unique_lock(const unique_lock&) = delete;
    unique_lock& operator=(const unique_lock&) = delete;

    unique_lock(unique_lock&& __u) noexcept
    : _M_device(__u._M_device), _M_owns(__u._M_owns)
    {
  __u._M_device = 0;
  __u._M_owns = false;
    }

    unique_lock& operator=(unique_lock&& __u) noexcept
    {
  if(_M_owns)
    unlock();

  unique_lock(std::move(__u)).swap(*this);

  __u._M_device = 0;
  __u._M_owns = false;

  return *this;
    }

    void
    lock()
    {
  if (!_M_device)
    __throw_system_error(int(errc::operation_not_permitted));
  else if (_M_owns)
    __throw_system_error(int(errc::resource_deadlock_would_occur));
  else
    {
      _M_device->lock();
      _M_owns = true;
    }
    }

    bool
    try_lock()
    {
  if (!_M_device)
    __throw_system_error(int(errc::operation_not_permitted));
  else if (_M_owns)
    __throw_system_error(int(errc::resource_deadlock_would_occur));
  else
    {
      _M_owns = _M_device->try_lock();
      return _M_owns;
    }
    }

    template<typename _Clock, typename _Duration>
  bool
  try_lock_until(const chrono::time_point<_Clock, _Duration>& __atime)
  {
    if (!_M_device)
      __throw_system_error(int(errc::operation_not_permitted));
    else if (_M_owns)
      __throw_system_error(int(errc::resource_deadlock_would_occur));
    else
      {
        _M_owns = _M_device->try_lock_until(__atime);
        return _M_owns;
      }
  }

    template<typename _Rep, typename _Period>
  bool
  try_lock_for(const chrono::duration<_Rep, _Period>& __rtime)
  {
    if (!_M_device)
      __throw_system_error(int(errc::operation_not_permitted));
    else if (_M_owns)
      __throw_system_error(int(errc::resource_deadlock_would_occur));
    else
      {
        _M_owns = _M_device->try_lock_for(__rtime);
        return _M_owns;
      }
   }

    void
    unlock()
    {
  if (!_M_owns)
    __throw_system_error(int(errc::operation_not_permitted));
  else if (_M_device)
    {
      _M_device->unlock();
      _M_owns = false;
    }
    }

    void
    swap(unique_lock& __u) noexcept
    {
  std::swap(_M_device, __u._M_device);
  std::swap(_M_owns, __u._M_owns);
    }

    mutex_type*
    release() noexcept
    {
  mutex_type* __ret = _M_device;
  _M_device = 0;
  _M_owns = false;
  return __ret;
    }

    bool
    owns_lock() const noexcept
    { return _M_owns; }

    explicit operator bool() const noexcept
    { return owns_lock(); }

    mutex_type*
    mutex() const noexcept
    { return _M_device; }

  private:
    mutex_type*	_M_device;
    bool		_M_owns; // XXX use atomic_bool
  };



}
#endif // WIN32STDMUTEX_H
