#pragma once

#include "DrawableObject.hpp"
#include <string>

class Font : public DrawableObject
{
public:
  Font(){}
  virtual ~Font(){}
  
  virtual void	draw(double /*elapsedTime*/ = 0){}
  virtual void	draw(int /*x*/, int /*y*/, double /*elapsedTime*/ = 0){}
  virtual void	setText(std::string const & /*text*/) {}
  virtual void	setColor(int, int, int) {}
  
  virtual int	getWidth() {return 0;}
  virtual int	getHeight() {return 0;}
};
