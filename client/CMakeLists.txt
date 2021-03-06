cmake_minimum_required (VERSION 2.8)

project(Grab_Client)
set(TARGET_NAME grab_client)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

##### Linking the sfml libraries
IF(WIN32)
set(TYPE "Windows")
set(SFML_INCLUDE_DIR "C:/Development/Environment/SFML-1.6/include")
set(SFMLDIR "C:/Development/Environment/SFML-1.6")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 1.6 REQUIRED SYSTEM AUDIO GRAPHICS WINDOW)
set(SFML_LIBRARIES
	${SFML_GRAPHICS_LIBRARY}
	${SFML_WINDOW_LIBRARY}
	${SFML_SYSTEM_LIBRARY}
	${SFML_AUDIO_LIBRARY}
)
ELSEIF(LINUX)
set(TYPE "Linux")
set(SFML_INCLUDE_DIR "/usr/include/SFML")
set(SFML_LIBRARIES
	sfml-graphics
	sfml-window
	sfml-audio
	sfml-system
)
ELSE(LINUX)
set(TYPE "BSD")
set(SFML_INCLUDE_DIR "/usr/local/include/")
LINK_DIRECTORIES ("/usr/local/lib/")
set(SFML_LIBRARIES
	sfml-graphics
	sfml-window
	sfml-audio
	sfml-system
)
ENDIF(WIN32)
#####

##### Linking openal
find_package(OpenAL)
find_package(sndfile)


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


set(GUI_INCLUDE_DIR "gui")

set(GUI_SRC_DIR "gui")
set(INCLUDES_COMMON_DIR "../common/")

set(SRCS
	${INCLUDES_CORE}
	${INCLUDES_COMMON_DIR}BlackHole.hpp
	${INCLUDES_COMMON_DIR}BlackHole.cpp
	${INCLUDES_COMMON_DIR}BlackHolePower.hpp
	${INCLUDES_COMMON_DIR}BlackHolePower.cpp
	${INCLUDES_COMMON_DIR}Missile.hpp
	${INCLUDES_COMMON_DIR}Missile.cpp
	${INCLUDES_COMMON_DIR}Shield.hpp
	${INCLUDES_COMMON_DIR}Shield.cpp	
	${INCLUDES_COMMON_DIR}SpecialPower.hpp
	${INCLUDES_COMMON_DIR}SpecialPower.cpp	
	${INCLUDES_COMMON_DIR}PacketType.hpp
	${INCLUDES_COMMON_DIR}Resources.hpp
	${INCLUDES_COMMON_DIR}Resources.cpp
	${INCLUDES_COMMON_DIR}GameCommand.hpp
	${INCLUDES_COMMON_DIR}Map.hpp
	${INCLUDES_COMMON_DIR}Map.cpp
	${INCLUDES_COMMON_DIR}Modes.hpp
	${INCLUDES_COMMON_DIR}MonsterGenerator.hpp
	${INCLUDES_COMMON_DIR}MonsterGenerator.cpp
	${INCLUDES_COMMON_DIR}MapProvider.hpp
	${INCLUDES_COMMON_DIR}MapProvider.cpp
	${INCLUDES_COMMON_DIR}ShipInfo.hpp
	${INCLUDES_COMMON_DIR}PlayerBullet.cpp
	${INCLUDES_COMMON_DIR}PlayerBullet.hpp
	${INCLUDES_COMMON_DIR}Cannon.hpp
	${INCLUDES_COMMON_DIR}Cannon.cpp
	${INCLUDES_COMMON_DIR}DestroyCommand.hpp
	${INCLUDES_COMMON_DIR}DestroyCommand.cpp
	${INCLUDES_COMMON_DIR}CompositeMonsterProvider.hpp
	${INCLUDES_COMMON_DIR}CompositeMonsterProvider.cpp
	${INCLUDES_COMMON_DIR}CompositeMonster.hpp
	${INCLUDES_COMMON_DIR}CompositeMonster.cpp
	${INCLUDES_COMMON_DIR}CompositeMaster.hpp
	${INCLUDES_COMMON_DIR}CompositeMaster.cpp
	${INCLUDES_COMMON_DIR}CompositeNode.hpp
	${INCLUDES_COMMON_DIR}CompositeNode.cpp
	main.cpp
	SFMLFont.cpp
	SFMLFont.hpp
	SFMLFontProvider.cpp
	SFMLFontProvider.hpp
	SFMLMusic.hpp
	SFMLMusic.cpp
	${INCLUDES_COMMON_DIR}ConcreteObject.cpp
	${INCLUDES_COMMON_DIR}ConcreteObject.hpp
	Game.cpp
	Game.hpp
	GameButton.cpp
	GameButton.hpp
	GameListCommand.hpp
	GameListCommand.cpp
	${INCLUDES_COMMON_DIR}Grab.hpp
	${INCLUDES_COMMON_DIR}Grab.cpp
	GSBindPlayer.cpp
	GSBindPlayer.hpp
	GSContinue.cpp
	GSContinue.hpp
	GSGameOver.cpp
	GSGameOver.hpp
	GSInGame.cpp
	GSInGame.hpp
	GSJoinGame.cpp
	GSJoinGame.hpp
	GSLoading.cpp
	GSLoading.hpp
	GSMapChoice.cpp
	GSMapChoice.hpp
	GSModeSelection.cpp
	GSModeSelection.hpp
	GSOptions.cpp
	GSOptions.hpp
	GSPauseMenu.cpp
	GSPauseMenu.hpp
	GSPreload.cpp
	GSPreload.hpp
	GSMainMenu.cpp
	GSMainMenu.hpp
	GSPartySettings.cpp
	GSPartySettings.hpp
	GSSplashScreen.cpp
	GSSplashScreen.hpp
	InputModule.cpp
	InputModule.hpp
	main.cpp
	NetworkModule.cpp
	NetworkModule.hpp
	OpenALSoundProvider.cpp
	OpenALSoundProvider.hpp
	OpenALSound.cpp
	OpenALSound.hpp
	PacketCommand.cpp
	PacketCommand.hpp
	Player.cpp
	Player.hpp
	RendererManager.cpp
	RendererManager.hpp
	ResourceCommand.hpp
	Rules.cpp
	Rules.hpp
	ScrollingSprite.hpp
	ScrollingSprite.cpp
	Server.cpp
	Server.hpp
	ScoreBonus.cpp
	ScoreBonus.hpp
	SFMLSprite.cpp
	SFMLSprite.hpp
	SFMLSpriteProvider.cpp
	SFMLSpriteProvider.hpp
	${INCLUDES_COMMON_DIR}Ship.cpp
	${INCLUDES_COMMON_DIR}Ship.hpp
	UdpHandler.cpp
	UdpHandler.hpp
	Wall.cpp
	Wall.hpp
	${GUI_SRC_DIR}/GUIButton.hpp
	${GUI_SRC_DIR}/GUIBindButton.hpp
	${GUI_SRC_DIR}/GUIBindButton.cpp
	${GUI_SRC_DIR}/GUILabel.cpp
	${GUI_SRC_DIR}/GUILabel.hpp
	${GUI_SRC_DIR}/GUIList.hpp
	${GUI_SRC_DIR}/GUIPlayerButton.cpp
	${GUI_SRC_DIR}/GUIPlayerButton.hpp
	${GUI_SRC_DIR}/GUITextBox.hpp
	${GUI_SRC_DIR}/GUIVLayout.cpp
	${GUI_SRC_DIR}/GUIHLayout.cpp
	${GUI_SRC_DIR}/GUIVLayout.hpp
	${GUI_SRC_DIR}/GUIHLayout.hpp
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
  "-W -Wall -Wextra -g3 -D_CLIENT_")
ENDIF(WIN32)

##### Setting the output directory for the solution
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../ )

foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/../ )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
#####

IF(WIN32)
add_executable(
	${TARGET_NAME} WIN32 resource.rc
	${SRCS}	
)
ELSE(WIN32)
add_executable(
	${TARGET_NAME}
	${SRCS}
)
ENDIF(WIN32)

include_directories (
	${INCLUDES_COMMON_DIR}
	${SFML_INCLUDE_DIR}
	${OPENAL_INCLUDE_DIR}
	${SNDFILE_INCLUDE_DIR}
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
	${CORE_DIR}
	${CORE_CALLBACK_DIR}
	${COMMON_INCLUDE_DIR}
	${CORE_QUADTREE_INCLUDE_DIR}
	${CORE_BULLETML_DIR}
	${CORE_TINYXML_DIR}
	${GUI_INCLUDE_DIR}
	./
)

find_package (Threads)

IF(WIN32)
#add_subdirectory(../common/libnet ../common/libnet_build_2)
	add_subdirectory(../common/core ../common/libcore_build_2)
ELSE(WIN32)
#add_subdirectory(../common/libnet ../common/libnet_build)
	add_subdirectory(../common/core ../common/libcore_build)
ENDIF(WIN32)

###### linking net to core

target_link_libraries(
	${TARGET_NAME}
	${SFML_LIBRARIES}
	${OPENAL_LIBRARY}
	${SNDFILE_LIBRARY}
	${CMAKE_THREAD_LIBS_INIT}
	core
	net
)
