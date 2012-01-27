/*
 * NetDef.hpp
 *
 *  Created on: Dec 8, 2011
 *      Author: snap
 */

#ifndef NETDEF_HPP_
#define NETDEF_HPP_

#ifndef NET_DLLREQ
	#if defined (NETDLL)
		#if defined (_WIN32)
			#define	NET_DLLREQ //__declspec(dllexport)
		#else
			#define NET_DLLREQ
		#endif
	#else
		#if defined (_WIN32)
			#define	NET_DLLREQ //__declspec(dllimport)
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

#endif /* NETDEF_HPP_ */
