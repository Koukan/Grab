#include "Net.hpp"
#include <iostream>

using namespace Net;

class	Client : public RingBufferPacketHandler<>
{
public:
	Client() : RingBufferPacketHandler(1500, "\n")
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

  Net::DefaultSyncPolicy reactor;
/*  Acceptor<Client>		acceptor;

  acceptor.setup(test, *reactor);*/
  Connector<Client>		connector;
  connector.setup(test, reactor, false);
  reactor.waitForEvent(-1);
  return (0);
}
