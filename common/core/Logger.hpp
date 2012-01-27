#pragma once
#include <iostream>
#include "Net.hpp"

class Logger
{
private:
  class Log
  {
  public:
	Log()
	{
	}
    Log(Log const &)
	{
	}

    ~Log()
    {
      std::cout << std::endl;
    }

    template<typename T>
    Log& operator<<(T const &t)
    {
      std::cout << t;
      return (*this);
    }
  };

public:
	Logger(){}

  template<typename T>
  Log operator<<(T const &t)
  {
    Log log;

    log << "[" << Net::Clock::getTimeInStr() << "] ";
    log << t;

    return (log);
  }

  static Logger logger;
};
