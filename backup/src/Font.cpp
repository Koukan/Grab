#include "Font.hpp"
#include "RendererManager.hpp"

GameFont::GameFont(const CL_StringRef & resource_id, CL_ResourceManager &resources, double x, double y)
  : DrawableObject(x, y), CL_Font_Freetype(resource_id, &resources)
{}

GameFont::~GameFont(void)
{
}

void GameFont::draw()
{
  this->CL_Font_Freetype::draw_text(RendererManager::get().getGC(),
		  static_cast<float>(this->_x),
		  static_cast<float>(this->_y), _text, _color);
}

void GameFont::draw(int x, int y)
{
  this->CL_Font_Freetype::draw_text(RendererManager::get().getGC(), x, y, _text, _color);
}

void GameFont::setText(std::string const &string)
{
  _text = string;
}

std::string const 	&GameFont::getText() const
{
  return _text;
}

void			GameFont::setColor(CL_Colorf &color)
{
  _color = color;
}

CL_Colorf const		&GameFont::getColor() const
{
  return _color;
}
