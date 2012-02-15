#pragma once

#include "GSManager.hpp"
#include "Singleton.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ GameStateManager : public GSManager, public Net::Singleton<GameStateManager>
{
  public:
    GameStateManager(){}
    virtual ~GameStateManager(){}
};

CORE_END_NAMESPACE
