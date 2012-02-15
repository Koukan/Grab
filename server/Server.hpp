#pragma once

#include "ModuleManager.hpp"
#include "ThreadPool.hpp"
#include "Singleton.hpp"
#include "GameManager.hpp"

#define     NBTHREAD    8

class Server : public Core::ModuleManager, public Net::Singleton<Server>,
			   public GameManager, public Net::ThreadPool
{
  public:
    Server();
    virtual ~Server();
	bool			initServer(std::string const &port = "25557", size_t nbthread = NBTHREAD);
};
