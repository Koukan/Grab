#pragma once

#include <ClanLib/Display/2D/sprite.h>
#include "DrawableObject.hpp"

class Sprite : public DrawableObject, public CL_Sprite
{
public:
	Sprite(CL_GraphicContext & gc, const CL_StringRef & fullname);
	Sprite(CL_GraphicContext & gc, const CL_StringRef & resource_id, CL_ResourceManager * resources);
	~Sprite(void);

	void Draw();

private:
	CL_GraphicContext & _gc;
};
