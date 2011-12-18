#if defined (WIN32)

# include "Mutex.hpp"

bool	WinMutex::lock(void)
{
  return (WaitForSingleObject(_handle, INFINITE) == WAIT_OBJECT_0);
}

bool	WinMutex::unlock(void)
{
  return (ReleaseMutex(_handle));
}

bool	WinMutex::tryLock(void)
{
  return (WaitForSingleObject(_handle, 0) == WAIT_OBJECT_0);
}

bool	WinMutex::timedLock(int sec, int nano)
{
  return (WaitForSingleObject(_handle, sec * 1000 + nano / 1000000) == WAIT_OBJECT_0);
}

WinMutex::WinMutex()
{
  _handle = CreateMutex(NULL, FALSE, NULL);
}

WinMutex::~WinMutex()
{
  CloseHandle(_handle);
}
#endif