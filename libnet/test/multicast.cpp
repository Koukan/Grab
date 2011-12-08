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
#include "UdpPacketHandler.hpp"
#include <iostream>

using namespace Net;

typedef EpollPolicy Policy;

class	Client : public UdpPacketHandler
{
public:
	Client()
	{
	}

	virtual void init()
	{
	  _reactor->scheduleTimer(*this, 3000, true);
	  InetAddr				test("224.0.102.129", "4096");
  	  std::cout << "addr " << test.getHost() << " is multicast : " << test.isMulticast() << std::endl;
	  std::cout << this->join(test) << std::endl;
	  std::cout << this->setTTLMulticast(3, test) << std::endl;
	  printLastError();
	}

	virtual int handleInputPacket(Packet &input)
	{
		std::string	res;

		input >> res;
		std::cout << res << " from " << input.getAddr().getHost(NI_NUMERICHOST) << std::endl;
		return 1;
	}

	virtual int handleTimeout()
	{
	  std::cout << "timeout" << std::endl;
	  Packet	packet(45);

	  packet << "multicast";
	  InetAddr              mul("224.0.102.129", "4096");
	  packet.setDestination(mul);
	  this->handleOutputPacket(packet);
	  return 0;
	}

private:
};


int  main(int ac, char **av)
{
  SetupNetwork  		init;
  InetAddr				b("4096");
  Reactor				*reactor = new Policy();
  Client				client;

  std::cout << "setup " << client.setup(b) << std::endl;
  client.setReactor(*reactor);
  client.init();
  reactor->registerHandler(client, client, Reactor::READ);
  return  reactor->waitForEvent();
}
