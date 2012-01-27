#include "Sprite.hpp"
#include "RendererManager.hpp"

Sprite::Sprite(const CL_StringRef & fullname, double x, double y)
  : DrawableObject(x, y), CL_Sprite(RendererManager::get().getGC(), fullname)
{}

Sprite::Sprite(const CL_StringRef & resource_id, CL_ResourceManager &resources, double x, double y)
  : DrawableObject(x, y), CL_Sprite(RendererManager::get().getGC(), resource_id, &resources)
{}

Sprite::~Sprite(void)
{
}

void Sprite::draw(double)
{
  this->CL_Sprite::update();
  this->CL_Sprite::draw(RendererManager::get().getGC(), static_cast<float>(this->_x), static_cast<float>(this->_y));
}

void Sprite::draw(int x, int y)
{
  this->CL_Sprite::update();
  this->CL_Sprite::draw(RendererManager::get().getGC(), x, y);
}
