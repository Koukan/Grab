#pragma once

#include <string>
#include "DrawableObject.hpp"
#include "Resource.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ CoreFont : public DrawableObject, public Resource
{
public:
	CoreFont(double x = 0, double y = 0) : DrawableObject(x, y){}
	virtual ~CoreFont(){}

	virtual void	draw(double /*elapsedTime*/ = 0){}
	virtual void	draw(int /*x*/, int /*y*/, double /*elapsedTime*/ = 0){}

	// setter
	virtual void	setText(std::string const & /*text*/){}
	virtual void	setColor(int, int, int) {}
	virtual void	setTransparency(int) {}

	// getter
	virtual int		getWidth() const {return 0;}
	virtual int		getHeight() const {return 0;}
};

CORE_END_NAMESPACE
