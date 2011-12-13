#ifndef _NETWORK_
#define _NETWORK_

#if defined (_WIN32)
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include	<stdint.h>
#	include <windows.h>
#	define	poll WSAPoll
#	pragma comment(lib, "Ws2_32.lib")
typedef	char	sockopt;
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <sys/uio.h>
#	include <arpa/inet.h>
#	include <netdb.h>
#	include <netinet/in.h>
#	include <signal.h>
#	include <fcntl.h>
#	include <errno.h>
#	define	ioctlsocket	fcntl
#  	define	closesocket close
#  	define	SOCKET int
typedef socklen_t	sockopt;
#endif

#define ntohll(x) (((uint64_t)(ntohl((uint32_t)((x << 32) >> 32))) << 32) | \
                   (uint64_t)ntohl(((uint32_t)(x >> 32))))

#define htonll(x) ntohll(x)

#define	Handle SOCKET

# ifndef	INVALID_SOCKET
#  define	INVALID_SOCKET -1
# endif		/* !INVALID_SOCKET*/

#define INVALID_HANDLE INVALID_SOCKET

# ifndef	SHUT_RD
#  define	SHUT_RD SD_RECEIVE
# endif		/* !SHUT_RD*/

# ifndef	SHUT_WR
#  define	SHUT_WR SD_SEND
# endif		/* !SHUT_WR */

# ifndef	SHUT_RDWR
#  define	SHUT_RDWR SD_BOTH
# endif		/* !SHUT_WR */

# if	!defined (__socklen_t_defined) && !defined (_SOCKLEN_T_DECLARED)
typedef int	socklen_t;
# endif		/* !__socklen_t_defined && _SOCKLEN_T_DECLARED */

#ifndef	UIO_MAXIOV
#  define UIO_MAXIOV 1024
#endif

#if defined(_WIN32)
struct	iovec
{
	u_long		iov_len;
	char FAR	*iov_base;
};
#endif

#define BACKLOG	10

typedef struct pollfd pollfd;

#include "Error.hpp"

#endif /* _NETWORK_ */
