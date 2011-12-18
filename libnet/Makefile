NAMESTATIC		=  libnet.a
NAMEDYNAMIC		=  libnet.so

DIR		=  ./src

SRCS		= $(DIR)/InetAddr.cpp				\
				$(DIR)/Error.cpp				\
				$(DIR)/PacketHandler.cpp		\
				$(DIR)/Socket.cpp				\
				$(DIR)/SocketIO.cpp				\
				$(DIR)/SocketAcceptor.cpp		\
				$(DIR)/SocketConnector.cpp		\
				$(DIR)/SocketStream.cpp			\
				$(DIR)/SocketDatagram.cpp		\
				$(DIR)/SetupNetwork.cpp			\
				$(DIR)/NetHandler.cpp			\
				$(DIR)/Reactor.cpp				\
				$(DIR)/PollPolicy.cpp			\
				$(DIR)/EpollPolicy.cpp			\
				$(DIR)/KqueuePolicy.cpp			\
				$(DIR)/Packet.cpp				\
				$(DIR)/DataBlock.cpp			\
				$(DIR)/UdpPacketHandler.cpp		\
				$(DIR)/IOVec.cpp				\
				$(DIR)/thread/PosixMutex.cpp	\
				$(DIR)/thread/PosixThread.cpp	\
				$(DIR)/thread/TSS.cpp			\
				$(DIR)/thread/WinMutex.cpp		\
				$(DIR)/thread/WinThread.cpp


OBJS		= $(SRCS:.cpp=.o)

CC		= g++

RM		= rm -f

AR		= ar r

RANLIB		= ranlib

CXXFLAGS	= -W -Wall -Wextra -O2 -pipe -fPIC -I include/ -I include/thread

LDFLAGS		= 


$(NAMESTATIC)		: $(OBJS)
					$(AR) $(NAMESTATIC) $(OBJS)
					$(RANLIB) $(NAMESTATIC)

$(NAMEDYNAMIC)		: $(OBJS)
					$(CC) $(OBJS) -shared -o $(NAMEDYNAMIC)

all		: $(NAMESTATIC) $(NAMEDYNAMIC)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAMESTATIC)
		$(RM) $(NAMEDYNAMIC)

re		: fclean all

