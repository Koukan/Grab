#pragma once

#include <string>
#include "DrawableObject.hpp"
#include "Resource.hpp"

class CoreFont : public DrawableObject, public Resource
{
public:
	CoreFont(double x = 0, double y = 0) : DrawableObject(x, y){}
	virtual ~CoreFont(){}

	virtual void	draw(double /*elapsedTime*/ = 0){}
	virtual void	draw(int /*x*/, int /*y*/, double /*elapsedTime*/ = 0){}

	// setter
	virtual void	setText(std::string const & /*text*/){}
	virtual void	setColor(int, int, int) {}

	// getter
	virtual int		getWidth() const {return 0;}
	virtual int		getHeight() const {return 0;}
};
