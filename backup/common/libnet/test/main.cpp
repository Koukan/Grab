#include "Net.hpp"
#include <iostream>

using namespace Net;


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
	  std::cout << _iohandler.getHandle() << std::endl;
	  std::cout << _iohandler.getRemoteAddr(addr) << std::endl;
	  std::cout << addr.getHost() << addr.getHost() << std::endl;
	}

	virtual int handleInputPacket(Packet &input)
	{
		std::string	str;
		input >> str;
		Packet	test(2048);
		test << str;
		test << "\n";
		std::cout << str << std::endl;
		for (int i = 0; i < 1000; i++)
	   	{
			this->handleOutputPacket(test);
		}
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
  Reactor				*reactor = new DefaultSyncPolicy();
  Acceptor<Client>		acceptor;

  acceptor.setup(test, *reactor);
  //testtss = new Client();
  //testtss->handleTimeout();
  /*Connector<Client>		client;
  client.setup(test, *reactor);*/
  return  reactor->waitForEvent();
}
