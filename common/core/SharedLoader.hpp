#ifndef _SHAREDLOADER_
#define _SHAREDLOADER_

#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <exception>

# if defined (_WIN32)
#  include <windows.h>

class SharedLoader
{
public:
	~SharedLoader()
	{
	  for_each(_dlhandles.begin(), _dlhandles.end(), FreeLibrary);
	}
	template<typename T>
	T 	load(std::string const &path, std::string const &name)
	{
	  HMODULE handle = LoadLibrary(path.c_str());
	  if (!handle)
	  {
	    throw std::exception();
	  }
	  void  *(*func)() = reinterpret_cast<void *(*)()>
		  (GetProcAddress(handle, name.c_str()));
	  if (!func)
	    throw std::exception();
	  _dlhandles.push_back(handle);
	  return static_cast<T>(func());
	}

	template<typename T, typename Arg>
	T 	load(std::string const &path, std::string const &name, Arg arg)
	{
	  HMODULE handle = LoadLibrary(path.c_str());
	  if (!handle)
	  {
	    throw std::exception();
	  }
	  void  *(*func)(Arg) = reinterpret_cast<void *(*)(Arg)>
		  (GetProcAddress(handle, name.c_str()));
	  if (!func)
	    throw std::exception();
	  _dlhandles.push_back(handle);
	  return static_cast<T>(func(arg));
	}

private:
	std::list<HMODULE>	_dlhandles;
};

# else
#  include <dlfcn.h>

class SharedLoader
{
public:
	~SharedLoader()
	{
	  for_each(_dlhandles.begin(), _dlhandles.end(), dlclose);
	}
	template<typename T>
	T 	load(std::string const &path, std::string const &name)
	{
	  void	*handle = dlopen(path.c_str(), RTLD_LAZY);
	  if (!handle)
	  {
	    throw std::exception();
	  }
	  void  *(*func)() = reinterpret_cast<void *(*)()>(dlsym(handle, name.c_str()));
	  if (!func)
	    throw std::exception();
	  _dlhandles.push_back(handle);
	  return static_cast<T>(func());
	}

	template<typename T, typename Arg>
	T 	load(std::string const &path, std::string const &name, Arg arg)
	{
	  void	*handle = dlopen(path.c_str(), RTLD_LAZY);
	  if (!handle)
	  {
	    throw std::exception();
	  }
	  void  *(*func)(Arg) = reinterpret_cast<void *(*)(Arg)>(dlsym(handle, name.c_str()));
	  if (!func)
	    throw std::exception();
	  _dlhandles.push_back(handle);
	  return static_cast<T>(func(arg));
	}

private:
	std::list<void *>	_dlhandles;
};
#endif

#endif /* _SHAREDLOADER_ */
