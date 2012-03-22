#include "Net.hpp"
#include <iostream>

using namespace Net;


class	Client : public UdpPacketHandler
{
public:
	Client() : UdpPacketHandler()
	{
	}

	virtual void init()
	{
	  _reactor->scheduleTimer(*this, 3000, true);
	  _reactor->registerHandler(this->getIOHandler(), *this, Reactor::READ);
	}

	virtual int handleInputPacket(Packet &input)
	{
		std::string	str;
		input >> str;
		Packet	*answer = input.clone();
		std::cout << str << " from " << input.getAddr().getHost() << ":" << input.getAddr().getPort() << std::endl;
		answer->setDestination(input.getAddr());
		for (int i = 0; i < 1; i++)
	   	{
			this->handleOutputPacket(*answer);
		}
		delete answer;
		return 1;
	}

	virtual int handleTimeout()
	{
	  std::cout << "timeout" << std::endl;
	  return 0;
	}

private:
};

//TSS<Client>		testtss;

int  main(int ac, char **av)
{
	 SetupNetwork  		init;
  	InetAddr			test("4500");
  	InetAddr			tmp("0.0.0.0", "7800");
  	Net::DefaultSyncPolicy reactor;

	Client				client;
	client.getIOHandler().setup(test);
	client.setReactor(reactor);
	client.init();
  //testtss = new Client();
  //testtss->handleTimeout();
  /*Connector<Client>		client;
  client.setup(test, *reactor);*/
  return  reactor.waitForEvent(-1);
}
