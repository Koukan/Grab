#if defined (WIN32) && _MSC_VER < 1700

# include "Mutex.hpp"

NET_USE_NAMESPACE

Mutex::Mutex()
{
	InitializeCriticalSection(&_mutex);
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&_mutex);
}

void	Mutex::lock(void)
{
	EnterCriticalSection(&_mutex);
}

void	Mutex::unlock(void)
{
	LeaveCriticalSection(&_mutex);
}

bool	Mutex::try_lock(void)
{
	return true;
}

Mutex::mutex_t *Mutex::native_handle()
{
	return &_mutex;
}

#elif defined (ANDROID)
# include "Mutex.hpp"

NET_USE_NAMESPACE

Mutex::Mutex()
{
	pthread_mutex_init(&_mutex, 0);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&_mutex);
}

void        Mutex::lock()
{
	pthread_mutex_lock(&_mutex);
}

void        Mutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
}

bool        Mutex::try_lock()
{
  	return pthread_mutex_trylock(&_mutex) != -1;
}

Mutex::mutex_t *Mutex::native_handle()
{
	return &_mutex;
}

#endif

#if (defined (WIN32) && _MSC_VER < 1700) || defined (ANDROID)

LockGuard::LockGuard(Mutex &mutex) : _mutex(mutex)
{
	_mutex.lock();
}

LockGuard::~LockGuard()
{
	_mutex.unlock();
}

UniqueLock::UniqueLock(Mutex &mutex) : _mutex(mutex)
{
	this->lock();
}

UniqueLock::~UniqueLock()
{
	this->unlock();
}

void UniqueLock::lock()
{
	_mutex.lock();
	_locked = true;
}

void UniqueLock::unlock()
{
	if (!_locked)
		return ;
	_mutex.unlock();
	_locked = false;
}

UniqueLock::operator Mutex&()
{
	return _mutex;
}

#endif

