#include "Logger.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"

Server::Server()
{
}

Server::~Server()
{
}

#include <iostream>
bool			Server::init(std::string const &port, size_t nbthread)
{
	NetworkModule		&network = NetworkModule::get();

	this->ModuleManager::init();
	if (!this->ThreadPool::init(nbthread))
	  {
	    Logger::logger << "Can't init threads";
	    return false;
	  }
	network.setPort(port);
	this->loadModule(CommandDispatcher::get());
	this->loadModule(network);
	this->update(0);
	return true;
}
