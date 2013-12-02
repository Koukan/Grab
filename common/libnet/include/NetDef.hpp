/*!
 \file NetDef.hpp
 \brief Define used by libnet
 \author Vivien Botton
 \version 1.0
 \date 2013-03-15
 */

#ifndef NETDEF_HPP_
#define NETDEF_HPP_

#if defined (__APPLE__)
#define	__unix__
#elif defined (__MACOSX__)
#define __unix__
#endif

#ifndef NET_DLLREQ
	#if defined (NETDLL)
		#if defined (_WIN32)
			#define	NET_DLLREQ __declspec(dllexport)
		#else
			#define NET_DLLREQ
		#endif
	#else
		#if defined (_WIN32)
			#define	NET_DLLREQ __declspec(dllimport)
		#else
			#define NET_DLLREQ
		#endif
	#endif
#endif

#ifndef NET_NAMESPACE
#define NET_NAMESPACE Net
#endif

#ifndef NET_BEGIN_NAMESPACE
#define NET_BEGIN_NAMESPACE namespace NET_NAMESPACE {
#endif

#ifndef NET_END_NAMESPACE
#define NET_END_NAMESPACE };
#endif

#ifndef NET_USE_NAMESPACE
#define NET_USE_NAMESPACE using namespace NET_NAMESPACE;
#endif

#if defined (_WIN32)
#	pragma warning( disable: 4251 4275 4305 4244 4355 4800 4996 4067)
#endif


/*!
 \brief Contains network and thread utility, and other things OS dependant
 */
NET_BEGIN_NAMESPACE
NET_END_NAMESPACE

#endif /* NETDEF_HPP_ */
