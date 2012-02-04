#pragma once

#include "DrawableObject.hpp"
#include <string>

class CoreFont : public DrawableObject
{
public:
  CoreFont(double x = 0, double y = 0) : DrawableObject(x, y){}
  virtual ~CoreFont(){}
  
  virtual void	draw(double /*elapsedTime*/ = 0){}
  virtual void	draw(int /*x*/, int /*y*/, double /*elapsedTime*/ = 0){}

  virtual void	setText(std::string const & /*text*/){}
  virtual void	setColor(int, int, int) {}
  
  virtual int	getWidth() const {return 0;}
  virtual int	getHeight() const {return 0;}
};
