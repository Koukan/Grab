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

typedef EpollPolicy Policy;

class	Client : public PacketHandler<>
{
public:
	Client() : PacketHandler(1500, "\n")
	{
	}

	virtual void init()
	{
	  _reactor->scheduleTimer(*this, 3000, true);
	  InetAddr addr;
	  std::cout << this->getRemoteAddr(addr) << std::endl;
	  std::cout << addr.getHost() << addr.getHost() << std::endl;
	}

	virtual int handleInputPacket(Packet &input)
	{
		Packet	test(2048);
		test << std::string("je teste");
		test << true;
		test << 256;
		test << std::string("\n");
		std::cout << test.size() << std::endl;
		this->handleOutputPacket(test);
		return 1;
	}

	virtual int handleTimeout()
	{
	  std::cout << "timeout" << std::endl;
	  return 0;
	}

private:
};


int  main(int ac, char **av)
{
  SetupNetwork  		init;
  InetAddr				test("4500");
  InetAddr				tmp("0.0.0.0", "7800");
  Reactor				*reactor = new Policy();
  Acceptor<Client>		acceptor;

  acceptor.setup(test, *reactor);
  /*Connector<Client>		client;
  client.setup(test, *reactor);*/
  return  reactor->waitForEvent();
}
