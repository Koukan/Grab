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
		Packet packet(64);
		packet << static_cast<uint8_t>(0);
		packet << "Koukan";
		packet << '\n';
		this->handleOutputPacket(packet);
		Packet	answer(64);
		answer << static_cast<uint8_t>(7);
		answer << static_cast<uint8_t>(4);
		answer << '\n';
		this->handleOutputPacket(answer);
	}

	virtual int handleInputPacket(Packet &input)
	{
		std::cout << "answer" << std::endl;
		return 1;
	}


private:
};


int  main(int ac, char **av)
{
  SetupNetwork  		init;
  InetAddr				test("127.0.0.1", "25557");
  Reactor				*reactor = new Policy();
/*  Acceptor<Client>		acceptor;

  acceptor.setup(test, *reactor);*/
  Connector<Client>		connector;
  connector.setup(test, *reactor, false);
  reactor->waitForEvent();
  return (0);
}
