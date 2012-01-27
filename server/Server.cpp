#include "Server.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"

Server::Server()
{
}

Server::~Server()
{
}

bool			Server::init(std::string const &port, size_t nbthread)
{
	NetworkModule		&network = NetworkModule::get();

	this->ModuleManager::init();
	if (!this->ThreadPool::init(nbthread))
		return false;
	network.setPort(port);
	this->loadModule(CommandDispatcher::get());
	this->loadModule(network);
	this->update(0);
	return true;
}
