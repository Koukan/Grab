cmake_minimum_required (VERSION 2.8)

project(LibCore)

set(EXECUTABLE_OUTPUT_PATH ./)

set(CORE_DIR
	"./"
)
set(CORE_CALLBACK_DIR
	"Callback_Impl/"
)
set(CORE_QUADTREE_INCLUDE_DIR
	"QuadTree/"
)
set(CORE_BULLETML_DIR
	"bulletml/"
)
set(CORE_TINYXML_DIR
	"tinyxml/"
)

set(NET_INCLUDE_DIR "../libnet/include/")

set(NET_MUTEX_INCLUDE_DIR "../libnet/include/thread/")

set(INCLUDES_CORE
	${CORE_DIR}Bullet.hpp
	${CORE_DIR}BulletCommand.hpp
	${CORE_DIR}BulletResourceManager.hpp
	${CORE_DIR}ButtonSprite.hpp
	${CORE_DIR}Callback.hpp
	${CORE_DIR}Callback.ipp
	${CORE_DIR}CircleHitBox.hpp
	${CORE_DIR}Command.hpp
	${CORE_DIR}CommandDispatcher.hpp
	${CORE_DIR}CommandHandler.hpp
	${CORE_DIR}Converter.hpp
	${CORE_DIR}DrawableObject.hpp
	${CORE_DIR}FontProvider.hpp
	${CORE_DIR}GameObject.hpp
	${CORE_DIR}GameObjectManager.hpp
	${CORE_DIR}GameObjectManager.ipp
	${CORE_DIR}GameState.hpp
	${CORE_DIR}GameStateManager.hpp
	${CORE_DIR}GameStateObserver.hpp
	${CORE_DIR}GUIManager.hpp
	${CORE_DIR}GUILayout.hpp
	${CORE_DIR}GUIElement.hpp
	${CORE_DIR}GSManager.hpp
	${CORE_DIR}HitBox.hpp
	${CORE_DIR}Input.hpp
	${CORE_DIR}InputManager.hpp
	${CORE_DIR}IPhysicsSubscriber.hpp
	${CORE_DIR}LoadXMLProvider.hpp
	${CORE_DIR}Logger.hpp
	${CORE_DIR}md5.h
	${CORE_DIR}Module.hpp
	${CORE_DIR}ModuleManager.hpp
	${CORE_DIR}NonCopyable.hpp
	${CORE_DIR}Observable.hpp
	${CORE_DIR}PhysicManager.hpp
	${CORE_DIR}PhysicObject.hpp
	${CORE_DIR}PhysicsSubscriber.hpp
	${CORE_DIR}PhysicsSubscriber2.hpp
	${CORE_DIR}PolyHitBox.hpp
	${CORE_DIR}RectHitBox.hpp
	${CORE_DIR}ResourceManager.hpp
	${CORE_DIR}SharedLoader.hpp
	${CORE_DIR}Sprite.hpp
	${CORE_DIR}SpriteProvider.hpp
	${CORE_DIR}TimeEffectManager.hpp
	${CORE_DIR}Singleton.hpp
	${CORE_CALLBACK_DIR}Callback_Impl.hpp
	${CORE_QUADTREE_INCLUDE_DIR}QuadTree.hpp
	${CORE_BULLETML_DIR}bulletmlparser.h
	${CORE_TINYXML_DIR}tinyxml.h
)

set(SRCS_CORE
	${INCLUDES_CORE}
	${CORE_DIR}Bullet.cpp
	${CORE_DIR}BulletCommand.cpp
	${CORE_DIR}BulletResourceManager.cpp
	${CORE_DIR}ButtonSprite.cpp
	${CORE_DIR}Callback.cpp
	${CORE_DIR}CircleHitBox.cpp
	${CORE_DIR}CommandDispatcher.cpp
	${CORE_DIR}CommandHandler.cpp
	${CORE_DIR}GameObject.cpp
	${CORE_DIR}GameObjectManager.cpp
	${CORE_DIR}GameState.cpp
	${CORE_DIR}GameStateObserver.cpp
	${CORE_DIR}FontProvider.cpp
	${CORE_DIR}GUIManager.cpp
	${CORE_DIR}GUILayout.cpp
	${CORE_DIR}GUIElement.cpp
	${CORE_DIR}GSManager.cpp
	${CORE_DIR}HitBox.cpp
	${CORE_DIR}InputManager.cpp
	${CORE_DIR}LoadXMLProvider.cpp
	${CORE_DIR}Logger.cpp
	${CORE_DIR}md5.cpp
	${CORE_DIR}Module.cpp
	${CORE_DIR}ModuleManager.cpp
	${CORE_DIR}PhysicManager.cpp
	${CORE_DIR}PhysicObject.cpp
	${CORE_DIR}PolyHitBox.cpp
	${CORE_DIR}RectHitBox.cpp
	${CORE_DIR}SpriteProvider.cpp
	${CORE_DIR}ResourceManager.cpp
	${CORE_DIR}XMLProvider.cpp
	${CORE_DIR}TimeEffectManager.cpp
	${CORE_QUADTREE_INCLUDE_DIR}QuadTree.cpp
	${CORE_QUADTREE_INCLUDE_DIR}Node.cpp
	${CORE_QUADTREE_INCLUDE_DIR}TreeElement.cpp
	${CORE_BULLETML_DIR}bulletmlparser.cc
	${CORE_BULLETML_DIR}bulletmlparser-tinyxml.cc
	${CORE_BULLETML_DIR}bulletmltree.cc
	${CORE_BULLETML_DIR}calc.cc
	${CORE_BULLETML_DIR}formula-variables.cc
	${CORE_BULLETML_DIR}bulletmlrunner.cc
	${CORE_BULLETML_DIR}bulletmlrunnerimpl.cc
	${CORE_TINYXML_DIR}tinyxml.cpp
	${CORE_TINYXML_DIR}tinyxmlerror.cpp
	${CORE_TINYXML_DIR}tinyxmlparser.cpp
	${CORE_CALLBACK_DIR}/Callback_Impl_Function.cpp
)
SOURCE_GROUP (core_headers FILES(${INCLUDES_CORE}))

include_directories (
	${CORE_DIR}
	${CORE_CALLBACK_DIR}
	${CORE_QUADTREE_INCLUDE_DIR}
	${CORE_BULLETML_DIR}
	${CORE_TINYXML_DIR}
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
)

IF(WIN32)
ELSE(WIN32)
set_source_files_properties (
  ${SRCS_CORE}
  PROPERTIES
  COMPILE_FLAGS
  "-W -Wall -g3"
)
ENDIF(WIN32)

add_library(
	core
	STATIC
	${SRCS_CORE}
)
