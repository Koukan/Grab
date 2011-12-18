#include "SetupNetwork.hpp"
#include "InetAddr.hpp"
#include "SocketAcceptor.hpp"
#include "IOVec.hpp"
#include "Reactor.hpp"
#include "NetHandler.hpp"
#include "Acceptor.hpp"
#include "Connector.hpp"
#include "PacketHandler.hpp"
#include "SyncPolicy.hpp"
#include "TSS.hpp"
#include <iostream>

using namespace Net;

typedef DefaultSyncPolicy Policy;


class	Client : public PacketHandler<>
{
public:
	Client() : PacketHandler<>(1500, "\n")
	{
	}

	virtual void init()
	{
	  _reactor->scheduleTimer(*this, 3000, true);
	  InetAddr addr;
	  std::cout << this->getRemoteAddr(addr) << std::endl;
	  std::cout << addr.getHost() << addr.getHost() << std::endl;
	  this->setNonBlocking(true);
	}

	virtual int handleInputPacket(Packet &input)
	{
		std::string	str;
		input >> str;
		Packet	test(2048);
		test << str;
		//test << true;
		//test << 256;
		test << "\n";
		std::cout << str << std::endl;
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

TSS<Client>		testtss;

int  main(int ac, char **av)
{
  SetupNetwork  		init;
  InetAddr				test("4500");
  InetAddr				tmp("0.0.0.0", "7800");
  Reactor				*reactor = new Policy();
  Acceptor<Client>		acceptor;

  acceptor.setup(test, *reactor);
  testtss = new Client();
  testtss->handleTimeout();
  /*Connector<Client>		client;
  client.setup(test, *reactor);*/
  return  reactor->waitForEvent();
}
