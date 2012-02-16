#pragma once

#ifndef CORE_DLLREQ
	#if defined (NETDLL)
		#if defined (_WIN32)
			#define	CORE_DLLREQ //__declspec(dllexport)
		#else
			#define CORE_DLLREQ
		#endif
	#else
		#if defined (_WIN32)
			#define	CORE_DLLREQ //__declspec(dllimport)
		#else
			#define CORE_DLLREQ
		#endif
	#endif
#endif

#ifndef CORE_NAMESPACE
#define CORE_NAMESPACE Core
#endif

#ifndef CORE_BEGIN_NAMESPACE
#define CORE_BEGIN_NAMESPACE namespace CORE_NAMESPACE {
#endif

#ifndef CORE_END_NAMESPACE
#define CORE_END_NAMESPACE };
#endif

#ifndef CORE_USE_NAMESPACE
#define CORE_USE_NAMESPACE using namespace CORE_NAMESPACE;
#endif
