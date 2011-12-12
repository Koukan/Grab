NAME		=  ../Grab

DIR		=  .

SRCS		= $(DIR)/main.cpp								\
		  $(DIR)/Game.cpp									\
		  $(DIR)/Module.cpp									\
		  $(DIR)/ModuleManager.cpp                          \
		  $(DIR)/GameStateManager.cpp						\
		  $(DIR)/Callback.cpp								\
		  $(DIR)/InputManager.cpp							\
		  $(DIR)/Loading.cpp								\
		  $(DIR)/Event.cpp									\
		  $(DIR)/EventDispatcher.cpp						\
		  $(DIR)/GameObject.cpp								\
		  $(DIR)/GameObjectManager.cpp						\
		  $(DIR)/PhysicObject.cpp							\
		  $(DIR)/PhysicManager.cpp							\
		  $(DIR)/ManagerManager.cpp							\
		  $(DIR)/AudioManager.cpp							\
		  $(DIR)/RendererManager.cpp						\
		  $(DIR)/Sprite.cpp									\
		  $(DIR)/Callback_Impl/Callback_Impl_Function.cpp	\
		  $(DIR)/GameState.cpp								\
		  $(DIR)/BulletCommand.cpp							\
		  $(DIR)/Bullet.cpp									\
		  $(DIR)/BulletResourceManager.cpp					\
		  $(DIR)/TimeEffectManager.cpp						\
		  $(DIR)/PolyHitBox.cpp								\
		  $(DIR)/CircleHitBox.cpp							\
		  $(DIR)/HitBox.cpp									\
		  $(DIR)/RectHitBox.cpp								\
		  $(DIR)/GUIManager.cpp								\
		  $(DIR)/Sound.cpp									\
		  $(DIR)/SPARK/src/SPK_All.cpp						\
		  $(DIR)/SPARK/src/SPK_GL_All.cpp					\
		  $(DIR)/ParticleSystem.cpp							\
		  $(DIR)/Wall.cpp									\
		  $(DIR)/QuadTree/QuadTree.cpp						\
		  $(DIR)/QuadTree/Node.cpp							\
		  $(DIR)/QuadTree/TreeElement.cpp

OBJS		= $(SRCS:.cpp=.o)

CC		= g++

RM		= rm -f

CXXFLAGS	= -O2 -std=c++0x -pipe `pkg-config --cflags clanCore-2.3 clanNetwork-2.3 clanDisplay-2.3 clanGL-2.3 clanGL1-2.3 clanApp-2.3 clanMikMod-2.3 clanSound-2.3 clanVorbis-2.3` -I Callback_Impl -I bulletml -I SPARK/include -I QuadTree

LDFLAGS		= `pkg-config --libs clanCore-2.3 clanGUI-2.3 clanNetwork-2.3 clanDisplay-2.3 clanGL-2.3 clanGL1-2.3 clanApp-2.3 clanMikMod-2.3 clanSound-2.3 clanVorbis-2.3` \
		  -lpthread -Lbulletml -lbulletml -lGL -lGLU -ldl

$(NAME)		: $(OBJS)
		make -C bulletml
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all

libclean:
	make clean -C bulletml

libfclean:
	make fclean -C bulletml

libre:
	make re -C bulletml
