#if defined(_WIN32)

#include "IOCompletionPortPolicy.hpp"

NET_USE_NAMESPACE

struct	IOdata
{
   OVERLAPPED Overlapped;
   WSABUF DataBuf;
   CHAR Buffer[DATA_BUFSIZE];
   DWORD BytesSEND;
   DWORD BytesRECV;
} ;

static DWORD WINAPI WorkerThread(LPVOID arg)
{
	HANDLE CompletionPort = (HANDLE) arg;
	DWORD BytesTransferred;
	DWORD SendBytes, RecvBytes;
	DWORD Flags;
	Socket	*socket;
	IOdata	*iodata;

	while (true)
	{
		if (GetQueuedCompletionStatus(CompletionPort, &BytesTransferred,                            (LPDWORD)socket, (LPOVERLAPPED *) &iodata, INFINITE) == 0)
			return 0;
		
		
	}
	return 0;
}

IOCompletionPortPolicy::IOCompletionPortPolicy()
{
	_iocompletionport = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	for(int i = 0; i < (int)SystemInfo.dwNumberOfProcessors * 2; i++)
	{
		CreateThread(0, 0, WorkerThread, _iocompletionport, 0, 0);
	}
}

IOCompletionPortPolicy::~IOCompletionPortPolicy()
{
}

int     registerHandler(Socket &socket, EventHandler &handler, int mask)
{
	if (socket.getEventHandler() == 0)
		CreateIoCompletionPort((HANDLE)socket.getHandle(), _iocompletionport, &socket, 0);
	socket.setEventHandler(&handler);
	return 0;
}

int     removeHandler(Socket &socket)
{
	return 0;
}

int     waitForEvent(int timeout)
{
	return 0;
}

#endif
