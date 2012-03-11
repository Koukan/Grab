#include "Net.hpp"
#include "Logger.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GlobalResourceManager.hpp"
#include "ResourceManager.hpp"
#include "bulletmlrunner.h"
#include "GlobalResourceManager.hpp"
#include "MapProvider.hpp"
#include "ServerSprite.hpp"
#include "ServerSpriteProvider.hpp"

Server::Server()
{
}

Server::~Server()
{
}

bool			Server::initServer(std::string const &port, size_t nbthread)
{
	NetworkModule			&network = NetworkModule::get();
	Core::ResourceManager	test;
	ServerSpriteProvider	*provider = new ServerSpriteProvider;

	srand(static_cast<unsigned int>(Net::Clock::getMsSinceEpoch()));
	Core::GlobalResourceManager::get().init();
	Core::GlobalResourceManager::get().addProvider(*new MapProvider);
	Core::GlobalResourceManager::get().addProvider(*provider);
	this->Core::ModuleManager::init();
	if (!this->ThreadPool::init(nbthread))
	{
		Core::Logger::logger << "Can't init threads";
	    return false;
	}
	network.setPort(port);
	this->loadModule(Core::CommandDispatcher::get());
	this->loadModule(network);

	// add player sprite
	ServerSprite		*sprite = new ServerSprite;
	sprite->setWidth(10);
	sprite->setHeight(10);
	sprite->addUse();
	provider->addSprite("player1", *sprite);
	sprite = new ServerSprite;
	sprite->setWidth(10);
	sprite->setHeight(10);
	sprite->addUse();
	provider->addSprite("player2", *sprite);
	sprite = new ServerSprite;
	sprite->setWidth(10);
	sprite->setHeight(10);
	sprite->addUse();
	provider->addSprite("player3", *sprite);
	sprite = new ServerSprite;
	sprite->setWidth(10);
	sprite->setHeight(10);
	sprite->addUse();
	provider->addSprite("player4", *sprite);

	this->update(0);
	return true;
}
