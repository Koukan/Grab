#include "SetupNetwork.hpp"
#include "InetAddr.hpp"
#include "SocketAcceptor.hpp"
#include "IOVec.hpp"
#include "Reactor.hpp"
#include "PollPolicy.hpp"
#include "EpollPolicy.hpp"
#include "WFMOPolicy.hpp"
#include "NetHandler.hpp"
#include "Acceptor.hpp"
#include "Connector.hpp"
#include "PacketHandler.hpp"
#include <iostream>

using namespace Net;

typedef EpollPolicy Policy;

class	Client : public PacketHandler<>
{
public:
	Client() : PacketHandler(1500, "\n")
	{
	}

	virtual	void init()
	{
	   Packet test(64);
	   test << std::string("c'est moi\n");
	   this->handleOutputPacket(test);
	}

	virtual int handleInputPacket(Packet const &input)
	{
		Packet	&test = *(input.duplicate());
		std::string	str;
		test >> str;
		std::cout << str << std::endl;
		bool		bo;
		test >> bo;
		std::cout << bo << std::endl;
		int		ret;
		test >> ret;
		std::cout << ret << std::endl;
		return 0;
	}


private:
};


int  main(int ac, char **av)
{
  SetupNetwork  		init;
  InetAddr				test("127.0.0.1", "4500");
  Reactor				*reactor = new Policy();
/*  Acceptor<Client>		acceptor;

  acceptor.setup(test, *reactor);*/
  Connector<Client>		connector;
  connector.setup(test, *reactor, false);
  reactor->waitForEvent();
  return (0);
}
