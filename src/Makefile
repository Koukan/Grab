NAME		=  ../Grab

DIR		=  .

SRCS		= $(DIR)/main.cpp						\
		  $(DIR)/Game.cpp						\
		  $(DIR)/GameStateManager.cpp					\
		  $(DIR)/Callback.cpp						\
		  $(DIR)/InputManager.cpp                                       \
		  $(DIR)/Loading.cpp						\
		  $(DIR)/Event.cpp						\
		  $(DIR)/EventDispatcher.cpp					\
		  $(DIR)/GameObject.cpp						\
		  $(DIR)/GameObjectManager.cpp					\
		  $(DIR)/PhysicObject.cpp					\
		  $(DIR)/PhysicManager.cpp					\
		  $(DIR)/ManagerManager.cpp					\
		  $(DIR)/AudioManager.cpp					\
		  $(DIR)/RendererManager.cpp					\
		  $(DIR)/Sprite.cpp						\
		  $(DIR)/Callback_Impl/Callback_Impl_Function.cpp		\
		  $(DIR)/GameState.cpp

OBJS		= $(SRCS:.cpp=.o)

CC		= g++

RM		= rm -f

CXXFLAGS	= -W -Wall -Wextra -O2 -pipe `pkg-config --cflags clanCore-2.3 clanNetwork-2.3 clanDisplay-2.3 clanGL-2.3 clanGL1-2.3 clanApp-2.3 clanMikMod-2.3 clanSound-2.3 clanVorbis-2.3` -I Callback_Impl

LDFLAGS		= `pkg-config --libs clanCore-2.3 clanNetwork-2.3 clanDisplay-2.3 clanGL-2.3 clanGL1-2.3 clanApp-2.3 clanMikMod-2.3 clanSound-2.3 clanVorbis-2.3` -lpthread

$(NAME)		: $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all

