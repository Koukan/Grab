#pragma once

#include "GSManager.hpp"
#include "Singleton.hpp"

class GameStateManager : public GSManager, public Net::Singleton<GameStateManager>
{
  public:
    GameStateManager(){}
    virtual ~GameStateManager(){}
};
