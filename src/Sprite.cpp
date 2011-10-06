#include "Sprite.hpp"

Sprite::Sprite(CL_GraphicContext & gc, const CL_StringRef & fullname)
	: DrawableObject(), CL_Sprite(gc, fullname), _gc(gc)
{
}

Sprite::Sprite(CL_GraphicContext & gc, const CL_StringRef & resource_id, CL_ResourceManager * resources)
	: DrawableObject(), CL_Sprite(gc, resource_id, resources), _gc(gc)
{
}

Sprite::~Sprite(void)
{
}

void Sprite::Draw()
{
	this->CL_Sprite::draw(this->_gc, static_cast<float>(this->_x), static_cast<float>(this->_y));
}