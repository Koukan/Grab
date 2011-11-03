#pragma once

#include <string>
#include <ClanLib/Display/Font/font_freetype.h>
#include "DrawableObject.hpp"

class GameFont : public DrawableObject, public CL_Font_Freetype
{
public:
  GameFont(const CL_StringRef & resource_id, CL_ResourceManager &resources, double x = 0, double y = 0);
  virtual ~GameFont();

  virtual void		draw();
  virtual void		draw(int x, int y);

  void			setText(std::string const &string);
  std::string const 	&getText() const;

  void			setColor(CL_Colorf &color);
  CL_Colorf const	&getColor() const;

private:
  std::string		_text;
  CL_Colorf		_color;
};
