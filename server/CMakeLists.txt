cmake_minimum_required (VERSION 2.8)

project(R-Type_Server)

set(EXECUTABLE_OUTPUT_PATH ../)

set(COMMON_INCLUDE_DIR "../common/")

set(NET_SRCS_DIR "../common/libnet/src/")
set(NET_INCLUDE_DIR "../common/libnet/include")
set(NET_MUTEX_INCLUDE_DIR "../common/libnet/include/thread/")
set(NET_MUTEX_SRCS_DIR "../common/libnet/src/thread/")

##### Linking core
set(CORE_DIR
	"../common/core/"
)
set(CORE_CALLBACK_DIR
	"../common/core/Callback_Impl/"
)
set(CORE_QUADTREE_INCLUDE_DIR
	"../common/core/QuadTree/"
)
set(CORE_BULLETML_DIR
	"../common/core/bulletml/"
)
set(CORE_TINYXML_DIR
	"../common/core/tinyxml/"
)

set(SRCS
	${INCLUDES_CORE}
	${COMMON_INCLUDE_DIR}Resources.hpp
	${COMMON_INCLUDE_DIR}Resources.cpp
	main.cpp
	File.cpp
	File.hpp
	Game.cpp
	Game.hpp
	GameCommand.hpp
	GameLogic.cpp
	GameLogic.hpp
	GameManager.cpp
	GameManager.hpp
	GameTask.cpp
	GameTask.hpp
	NetworkModule.cpp
	NetworkModule.hpp
	PacketCommand.cpp
	PacketCommand.hpp
	Player.cpp
	Player.hpp
	Rules.cpp
	Rules.hpp
	Server.cpp
	Server.hpp
	ServerResourceManager.cpp
	ServerResourceManager.hpp
	Ship.cpp
	Ship.hpp
	Task.hpp
	ThreadPool.cpp
	ThreadPool.hpp
	UdpHandler.cpp
	UdpHandler.hpp
	main.cpp
	BCommand.cpp
	BCommand.hpp
)

IF(WIN32)
ELSE(WIN32)
set_source_files_properties (
  ${SRCS}
  PROPERTIES
  COMPILE_FLAGS
  "-std=c++0x -W -Wall"
)
ENDIF(WIN32)

set (COMMON_FILES
	${COMMON_INCLUDE_DIR}PacketType.hpp
)

SOURCE_GROUP (common FILES(${COMMON_FILES}))

##### Setting the output directory for the solution
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
#####


add_executable(
	rtype_server
	${SRCS}
)

add_subdirectory(../common/libnet ../common/libnet_build)
add_subdirectory(../common/core ../common/libcore_build)

include_directories (
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
	${CORE_DIR}
	${CORE_CALLBACK_DIR}
	${CORE_QUADTREE_INCLUDE_DIR}
	${CORE_BULLETML_DIR}
	${CORE_TINYXML_DIR}
	${COMMON_INCLUDE_DIR}
	.
)

find_package (Threads)

target_link_libraries(
	rtype_server
	core
	net
	${CMAKE_THREAD_LIBS_INIT}
)
