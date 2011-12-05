NAME		=  libnet.a

DIR		=  ./src

SRCS		= $(DIR)/InetAddr.cpp			\
				$(DIR)/Error.cpp			\
				$(DIR)/PacketHandler.cpp	\
				$(DIR)/Socket.cpp			\
				$(DIR)/SocketIO.cpp			\
				$(DIR)/SocketAcceptor.cpp	\
				$(DIR)/SocketConnector.cpp	\
				$(DIR)/SocketStream.cpp		\
				$(DIR)/SocketDatagram.cpp	\
				$(DIR)/SetupNetwork.cpp		\
				$(DIR)/NetHandler.cpp		\
				$(DIR)/Reactor.cpp			\
				$(DIR)/PollPolicy.cpp		\
				$(DIR)/EpollPolicy.cpp		\
				$(DIR)/Packet.cpp			\
				$(DIR)/DataBlock.cpp		\
				$(DIR)/UdpPacketHandler.cpp	\
				$(DIR)/IOVec.cpp

OBJS		= $(SRCS:.cpp=.o)

CC		= g++

RM		= rm -f

AR		= ar r

RANLIB		= ranlib

CXXFLAGS	= -W -Wall -Wextra -O2 -pipe -I include/

LDFLAGS		= 

$(NAME)		: $(OBJS)
		$(AR) $(NAME) $(OBJS)
	        $(RANLIB) $(NAME)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all

