cmake_minimum_required (VERSION 2.8)

project(Grab_Server)

set(COMMON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../common/")

set(NET_SRCS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../common/libnet/src/")
set(NET_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../common/libnet/include")
set(NET_MUTEX_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../common/libnet/include/thread/")
set(NET_MUTEX_SRCS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../common/libnet/src/thread/")

##### Linking core
set(CORE_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/../common/core/"
)
set(CORE_CALLBACK_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/../common/core/Callback_Impl/"
)
set(CORE_QUADTREE_INCLUDE_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/../common/core/QuadTree/"
)
set(CORE_BULLETML_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/../common/core/bulletml/"
)
set(CORE_TINYXML_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/../common/core/tinyxml/"
)

set(SRCS
	${INCLUDES_CORE}
	${COMMON_INCLUDE_DIR}BlackHole.hpp
	${COMMON_INCLUDE_DIR}BlackHole.cpp
	${COMMON_INCLUDE_DIR}BlackHolePower.hpp
	${COMMON_INCLUDE_DIR}BlackHolePower.cpp
	${COMMON_INCLUDE_DIR}Missile.hpp
	${COMMON_INCLUDE_DIR}Missile.cpp
	${COMMON_INCLUDE_DIR}Shield.hpp
	${COMMON_INCLUDE_DIR}Shield.cpp	
	${COMMON_INCLUDE_DIR}SpecialPower.hpp
	${COMMON_INCLUDE_DIR}SpecialPower.cpp	
	${COMMON_INCLUDE_DIR}PacketType.hpp
	${COMMON_INCLUDE_DIR}PacketType.hpp
	${COMMON_INCLUDE_DIR}Resources.hpp
	${COMMON_INCLUDE_DIR}Resources.cpp
	${COMMON_INCLUDE_DIR}GameCommand.hpp
	${COMMON_INCLUDE_DIR}Map.hpp
	${COMMON_INCLUDE_DIR}Map.cpp
	${COMMON_INCLUDE_DIR}MonsterGenerator.cpp
	${COMMON_INCLUDE_DIR}MonsterGenerator.hpp
	${COMMON_INCLUDE_DIR}MapProvider.hpp
	${COMMON_INCLUDE_DIR}MapProvider.cpp
	${COMMON_INCLUDE_DIR}Modes.hpp
	${COMMON_INCLUDE_DIR}Ship.hpp
	${COMMON_INCLUDE_DIR}Ship.cpp
	${COMMON_INCLUDE_DIR}Grab.hpp
	${COMMON_INCLUDE_DIR}Grab.cpp
	${COMMON_INCLUDE_DIR}Cannon.hpp
	${COMMON_INCLUDE_DIR}Cannon.cpp
	${COMMON_INCLUDE_DIR}ConcreteObject.hpp
	${COMMON_INCLUDE_DIR}ConcreteObject.cpp
	${COMMON_INCLUDE_DIR}PlayerBullet.hpp
	${COMMON_INCLUDE_DIR}PlayerBullet.cpp
	${COMMON_INCLUDE_DIR}DestroyCommand.hpp
	${COMMON_INCLUDE_DIR}DestroyCommand.cpp
	main.cpp
	Client.cpp
	Client.hpp
	Game.cpp
	Game.hpp
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
	ResourceCommand.hpp
	Rules.cpp
	Rules.hpp
	Server.cpp
	Server.hpp
	ServerSprite.hpp
	ServerSprite.cpp
	ServerSpriteProvider.hpp
	ServerSpriteProvider.cpp
	UdpHandler.cpp
	UdpHandler.hpp
	main.cpp
)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	if (CMAKE_COMPILER_IS_GNUCXX)
		add_definitions (-flto)
	endif()
endif(UNIX)
if(WIN32)
	add_definitions (/MP)
endif()

IF(WIN32)
ELSE(WIN32)
set_source_files_properties (
  ${SRCS}
  PROPERTIES
  COMPILE_FLAGS
  "-W -Wall -Wextra -g3"
)
ENDIF(WIN32)

#SOURCE_GROUP (common FILES(${COMMON_FILES}))

##### Setting the output directory for the solution
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../ )

foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/../ )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
#####

IF(WIN32)
add_executable(
	grab_server resource.rc
	${SRCS}
)
ELSE(WIN32)
add_executable(
	grab_server
	${SRCS}
)
ENDIF(WIN32)

#add_subdirectory(../common/libnet ../common/libnet_build)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../common/core ${CMAKE_CURRENT_SOURCE_DIR}/../common/libcore_build)

include_directories (
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
	${CORE_DIR}
	${CORE_CALLBACK_DIR}
	${CORE_QUADTREE_INCLUDE_DIR}
	${CORE_BULLETML_DIR}
	${CORE_TINYXML_DIR}
	${COMMON_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/.
)

find_package (Threads)

target_link_libraries(
	grab_server
	core
	net
	${CMAKE_THREAD_LIBS_INIT}
	rt
)
