#pragma once

#include "ModuleManager.hpp"
#include "ThreadPool.hpp"
#include "Singleton.hpp"
#include "GameManager.hpp"

#define     NBTHREAD    8

class Server : public ModuleManager, public Singleton<Server>,
			   public GameManager, public ThreadPool
{
  public:
    Server();
    virtual ~Server();
	bool			init(std::string const &port = "25557", size_t nbthread = NBTHREAD);
};
