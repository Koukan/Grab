cmake_minimum_required (VERSION 2.8)

project(R-Type_Client)

set(EXECUTABLE_OUTPUT_PATH ../)

##### Linking the sfml libraries
IF(WIN32)
set(TYPE "Windows")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(SFML_INCLUDE_DIR "C:/Development/Environment/SFML-1.6/include")
set(SFMLDIR "C:/Development/Environment/SFML-1.6")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 1.6 REQUIRED SYSTEM GRAPHICS WINDOW)
set(SFML_LIBRARIES
	${SFML_GRAPHICS_LIBRARY}
	${SFML_WINDOW_LIBRARY}
	${SFML_SYSTEM_LIBRARY}
)
ELSE(WIN32)
set(TYPE "Unix")
set(SFML_INCLUDE_DIR "/usr/include/SFML")
set(SFML_LIBRARIES
	sfml-graphics
	sfml-window
	sfml-system
	dl
)
ENDIF(WIN32)
#####

##### Linking libnet
set(NET_SRCS_DIR "../common/libnet/src/")
set(NET_INCLUDE_DIR "../common/libnet/include")
set(NET_MUTEX_INCLUDE_DIR "../common/libnet/include/thread/")
set(NET_MUTEX_SRCS_DIR "../common/libnet/src/thread/")

##### Linking core
set(CORE_DIR "../common/core/")
set(CORE_CALLBACK_DIR "../common/core/Callback_Impl/")
set(CORE_QUADTREE_INCLUDE_DIR "../common/core/QuadTree/")
set(CORE_BULLETML_DIR "../common/core/bulletml/")
set(CORE_TINYXML_DIR "../common/core/tinyxml/")


set(TARGET_NAME rtype_client)

##	Font.cpp
##	Font.hpp
##	AudioManager.cpp
##	AudioManager.hpp
set(GUI_INCLUDE_DIR "gui")

set(GUI_SRC_DIR "gui")
set(INCLUDES_COMMON_DIR "../common/")

set(SRCS
	${INCLUDES_CORE}
	main.cpp
	SFMLFont.cpp
	SFMLFont.hpp
	SFMLFontProvider.cpp
	SFMLFontProvider.hpp
	ConcreteObject.cpp
	ConcreteObject.hpp
	Game.cpp
	Game.hpp
	GameButton.cpp
	GameButton.hpp
	GameCommand.hpp
	GameListCommand.hpp
	GameListCommand.cpp
	GSInGame.cpp
	GSInGame.hpp
	GSJoinGame.cpp
	GSJoinGame.hpp
	GSLoading.cpp
	GSLoading.hpp
	GSOptions.cpp
	GSOptions.hpp
	GSPauseMenu.cpp
	GSPauseMenu.hpp
	GSPreload.cpp
	GSPreload.hpp
	GSMainMenu.cpp
	GSMainMenu.hpp
	GSCreateMenu.cpp
	GSCreateMenu.hpp
	InputModule.cpp
	InputModule.hpp
	main.cpp
	NetworkModule.cpp
	NetworkModule.hpp
	PacketCommand.cpp
	PacketCommand.hpp
	${INCLUDES_COMMON_DIR}PacketType.hpp
	RendererManager.cpp
	RendererManager.hpp
	${INCLUDES_COMMON_DIR}Resources.hpp
	${INCLUDES_COMMON_DIR}Resources.cpp
	Rules.cpp
	Rules.hpp
	ScrollingSprite.hpp
	ScrollingSprite.cpp
	Server.cpp
	Server.hpp
	SFMLSprite.cpp
	SFMLSprite.hpp
	SFMLSpriteProvider.cpp
	SFMLSpriteProvider.hpp
	UdpHandler.cpp
	UdpHandler.hpp
	Wall.cpp
	Wall.hpp
	${GUI_SRC_DIR}/GUIButton.hpp
	${GUI_SRC_DIR}/GUILabel.cpp
	${GUI_SRC_DIR}/GUILabel.hpp
	${GUI_SRC_DIR}/GUIList.hpp
	${GUI_SRC_DIR}/GUITextBox.hpp
	${GUI_SRC_DIR}/GUIVLayout.cpp
	${GUI_SRC_DIR}/GUIHLayout.cpp
	${GUI_SRC_DIR}/GUIVLayout.hpp
	${GUI_SRC_DIR}/GUIHLayout.hpp
)

IF(WIN32)
ELSE(WIN32)
set_source_files_properties (
  ${SRCS}
  PROPERTIES
  COMPILE_FLAGS
  "-std=c++0x -W -Wall -g3"
)
ENDIF(WIN32)

##### Setting the output directory for the solution
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
#####


add_executable(
	${TARGET_NAME}
	${SRCS}
)

include_directories (
	${INCLUDES_COMMON_DIR}
	${SFML_INCLUDE_DIR}
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
	${CORE_DIR}
	${CORE_CALLBACK_DIR}
	${COMMON_INCLUDE_DIR}
	${CORE_QUADTREE_INCLUDE_DIR}
	${CORE_BULLETML_DIR}
	${CORE_TINYXML_DIR}
	${GUI_INCLUDE_DIR}
)

find_package (Threads)
add_subdirectory(../common/libnet ../common/libnet_build)
add_subdirectory(../common/core ../common/libcore_build)

###### linking net to core

target_link_libraries(
	${TARGET_NAME}
	${SFML_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	core
	net
)
