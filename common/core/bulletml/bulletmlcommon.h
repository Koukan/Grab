#ifndef bulletmlcommon_h_
#define bulletmlcommon_h_

#ifdef COREDLL
#	if defined (_WIN32)
#		define DECLSPEC __declspec(dllexport)
#	else
#		define DECLSPEC
#	endif
#else
# define DECLSPEC
#endif

#if defined (_WIN32)
#include <memory>
#define bullet_shared_ptr std::shared_ptr
#else
#include <tr1/memory>
#define bullet_shared_ptr std::tr1::shared_ptr
#endif

#endif // ! bulletmlcommon_h_
