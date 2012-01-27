#pragma once

#include "GSManager.hpp"
#include "Singleton.hpp"

class GameStateManager : public GSManager, public Singleton<GameStateManager>
{
  public:
    GameStateManager(){}
    virtual ~GameStateManager(){}
};
