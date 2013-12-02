cmake_minimum_required (VERSION 2.8)

project(LibNet)
include (CheckFunctionExists)
check_function_exists (epoll_create HAVE_EPOLL)
check_function_exists (kqueue HAVE_KQUEUE)
check_function_exists (WaitForMultipleObjects HAVE_WFMO)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../ )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../)

#foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
#    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
#    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/../../ )
#    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/../../)
#endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

##### Linking libnet
set(NET_SRCS_DIR "src/")
set(NET_INCLUDE_DIR "include/")
set(NET_MUTEX_INCLUDE_DIR "include/thread/")
set(NET_MUTEX_SRCS_DIR "src/thread/")


option(BUILD_NET_EXAMPLES "Build examples" OFF)

set(INCLUDES_NET
	${NET_INCLUDE_DIR}Acceptor.hpp
	${NET_INCLUDE_DIR}AtomicInt.hpp
	${NET_INCLUDE_DIR}Base64.hpp
	${NET_INCLUDE_DIR}Clock.hpp
	${NET_INCLUDE_DIR}Connector.hpp
	${NET_INCLUDE_DIR}Converter.hpp
	${NET_INCLUDE_DIR}DataBlock.hpp
	${NET_INCLUDE_DIR}Directory.hpp
	${NET_INCLUDE_DIR}EpollPolicy.hpp
	${NET_INCLUDE_DIR}Error.hpp
	${NET_INCLUDE_DIR}Factory.hpp
	${NET_INCLUDE_DIR}HTTP.hpp
	${NET_INCLUDE_DIR}InetAddr.hpp
	${NET_INCLUDE_DIR}KqueuePolicy.hpp
	${NET_INCLUDE_DIR}Net.hpp
	${NET_INCLUDE_DIR}NetDef.hpp
	${NET_INCLUDE_DIR}EventHandler.hpp
	${NET_INCLUDE_DIR}FileMapping.hpp
	${NET_INCLUDE_DIR}FixedSizePacketHandler.hpp
	${NET_INCLUDE_DIR}Packet.hpp
	${NET_INCLUDE_DIR}PacketHandler.hpp
	${NET_INCLUDE_DIR}PollPolicy.hpp
	${NET_INCLUDE_DIR}PoolAllocator.hpp
	${NET_INCLUDE_DIR}PoolObject.hpp
	${NET_INCLUDE_DIR}PosixQueue.hpp
	${NET_INCLUDE_DIR}Reactor.hpp
	${NET_INCLUDE_DIR}SelectPolicy.hpp
	${NET_INCLUDE_DIR}Service.hpp
	${NET_INCLUDE_DIR}SetupNetwork.hpp
	${NET_INCLUDE_DIR}Socket.hpp
	${NET_INCLUDE_DIR}SocketAcceptor.hpp
	${NET_INCLUDE_DIR}SocketConnector.hpp
	${NET_INCLUDE_DIR}SocketDatagram.hpp
	${NET_INCLUDE_DIR}SocketIO.hpp
	${NET_INCLUDE_DIR}SocketStream.hpp
	${NET_INCLUDE_DIR}SyncPolicy.hpp
	${NET_INCLUDE_DIR}TimerSocket.hpp
	${NET_INCLUDE_DIR}Singleton.hpp
	${NET_INCLUDE_DIR}SizeHeaderPacketHandler.hpp
	${NET_INCLUDE_DIR}SHA1.hpp
	${NET_INCLUDE_DIR}RingBufferPacketHandler.hpp
	${NET_INCLUDE_DIR}ReliableUdpPacketHandler.hpp
	${NET_INCLUDE_DIR}UdpPacketHandler.hpp
	${NET_INCLUDE_DIR}WFMOPolicy.hpp
	${NET_INCLUDE_DIR}network.h
	${NET_MUTEX_INCLUDE_DIR}TaskExecuter.hpp
	${NET_MUTEX_INCLUDE_DIR}Mutex.hpp
	${NET_MUTEX_INCLUDE_DIR}Thread.hpp
	${NET_MUTEX_INCLUDE_DIR}ThreadPool.hpp
	${NET_MUTEX_INCLUDE_DIR}Task.hpp
	${NET_MUTEX_INCLUDE_DIR}TSS.hpp
	${NET_MUTEX_INCLUDE_DIR}ConditionVar.hpp
	${NET_MUTEX_INCLUDE_DIR}RWMutex.hpp	
)

set(SRCS_NET
	${INCLUDES_NET}
	${NET_SRCS_DIR}AtomicInt.cpp
	${NET_SRCS_DIR}Base64.cpp
	${NET_SRCS_DIR}Directory.cpp
	${NET_SRCS_DIR}HTTP.cpp
	${NET_SRCS_DIR}InetAddr.cpp
	${NET_SRCS_DIR}Error.cpp
	${NET_SRCS_DIR}SetupNetwork.cpp
	${NET_SRCS_DIR}SelectPolicy.cpp
	${NET_SRCS_DIR}Socket.cpp
	${NET_SRCS_DIR}SocketIO.cpp
	${NET_SRCS_DIR}SocketAcceptor.cpp
	${NET_SRCS_DIR}SocketConnector.cpp
	${NET_SRCS_DIR}SocketStream.cpp
	${NET_SRCS_DIR}SocketDatagram.cpp
	${NET_SRCS_DIR}EventHandler.cpp
	${NET_SRCS_DIR}FileMapping.cpp
	${NET_SRCS_DIR}Reactor.cpp
	${NET_SRCS_DIR}PollPolicy.cpp
	${NET_SRCS_DIR}PoolAllocator.cpp
	${NET_SRCS_DIR}PoolObject.cpp
	${NET_SRCS_DIR}PosixQueue.cpp
	${NET_SRCS_DIR}EpollPolicy.cpp
	${NET_SRCS_DIR}KqueuePolicy.cpp
	${NET_SRCS_DIR}WFMOPolicy.cpp
	${NET_SRCS_DIR}Packet.cpp
	${NET_SRCS_DIR}DataBlock.cpp
	${NET_SRCS_DIR}ReliableUdpPacketHandler.cpp
	${NET_SRCS_DIR}TimerSocket.cpp
	${NET_SRCS_DIR}UdpPacketHandler.cpp
	${NET_SRCS_DIR}Clock.cpp
	${NET_SRCS_DIR}SHA1.cpp
	${NET_MUTEX_SRCS_DIR}TaskExecuter.cpp
	${NET_MUTEX_SRCS_DIR}ThreadPool.cpp
	${NET_MUTEX_SRCS_DIR}NullMutex.cpp
	${NET_MUTEX_SRCS_DIR}PosixRWMutex.cpp
	${NET_MUTEX_SRCS_DIR}WinMutex.cpp
	${NET_MUTEX_SRCS_DIR}WinThread.cpp
	${NET_MUTEX_SRCS_DIR}WinConditionVar.cpp
	${NET_MUTEX_SRCS_DIR}WinRWMutex.cpp
)

SOURCE_GROUP (net_headers FILES(${INCLUDES_NET}))

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	if (CMAKE_COMPILER_IS_GNUCXX)
		add_definitions (-flto)
	endif()
endif(UNIX)
if(WIN32)
	add_definitions (/MP)
endif()

include_directories (
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
)

add_library(
	net
	SHARED
	${SRCS_NET}
)

add_definitions (-DNETDLL)

IF(HAVE_EPOLL)
set_source_files_properties (
  ${SRCS_NET}
  PROPERTIES
  COMPILE_FLAGS
  "-DHAVE_EPOLL"
)
ENDIF(HAVE_EPOLL)

IF(HAVE_KQUEUE)
set_source_files_properties (
  ${SRCS_NET}
  PROPERTIES
  COMPILE_FLAGS
  "-DHAVE_KQUEUE"
)
ENDIF(HAVE_KQUEUE)

if(BUILD_NET_EXAMPLES)

	set(HTTP_SRC test/main.cpp)
	add_executable(
		http
		${HTTP_SRC}
	)

	target_link_libraries(
		http
		net
		pthread
		rt
	)

	set(BENCH_SRC test/benchmarkpool.cpp)
	add_executable(
		benchmark_pool
		${BENCH_SRC}
	)

	target_link_libraries(
		benchmark_pool
		net
		pthread
		rt
	)


endif()
