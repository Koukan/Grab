#pragma once

#include <ClanLib/core.h>
#include "BulletResourceManager.hpp"

class ResourceManager : public CL_ResourceManager, public BulletResourceManager
{
  public:
    virtual ~ResourceManager(){}
};
