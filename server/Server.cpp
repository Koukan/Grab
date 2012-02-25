#include "Logger.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GlobalResourceManager.hpp"
#include "ResourceManager.hpp"
#include "bulletmlrunner.h"

Server::Server()
{
}

Server::~Server()
{
}

bool			Server::initServer(std::string const &port, size_t nbthread)
{
	NetworkModule		&network = NetworkModule::get();
	Core::ResourceManager		test;

	Core::GlobalResourceManager::get().init();
	//Core::GlobalResourceManager::get().addBulletParser("resources/BulletSinusoidal.xml", "test", test);
	//BulletMLRunner plop = BulletMLRunner(Core::GlobalResourceManager::get().getBulletParser("test"));
	this->Core::ModuleManager::init();
	if (!this->ThreadPool::init(nbthread))
	{
	  Core::Logger::logger << "Can't init threads";
	    return false;
	}
	network.setPort(port);
	this->loadModule(Core::CommandDispatcher::get());
	this->loadModule(network);
	this->update(0);
	return true;
}
