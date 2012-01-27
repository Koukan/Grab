#pragma once

#include <ClanLib/Display/Font/font_freetype.h>
#include "Font.hpp"

class GameFont : public CoreFont, public CL_Font_Freetype
{
public:
  GameFont(const CL_StringRef & resource_id, CL_ResourceManager &resources, double x = 0, double y = 0);
  virtual ~GameFont();

  virtual void		draw(double /*elapsedTime*/ = 0);
  virtual void		draw(int x, int y, double /*elapsedTime*/ = 0);

  void			setText(std::string const &string);
  std::string const 	&getText() const;

  void			setColor(CL_Colorf &color);
  CL_Colorf const	&getColor() const;

private:
  std::string		_text;
  CL_Colorf		_color;
};
