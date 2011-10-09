#pragma once

#include <ClanLib/Display/2D/sprite.h>
#include "DrawableObject.hpp"

class Sprite : public DrawableObject, public CL_Sprite
{
public:
  Sprite(const CL_StringRef & fullname, double x = 0, double y = 0);
  Sprite(const CL_StringRef & resource_id, CL_ResourceManager &resources, double x = 0, double y = 0);
  ~Sprite();

  virtual void		draw();
  virtual void		draw(int x, int y);
};
