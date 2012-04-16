#pragma once

#include <stdint.h>
#include "DrawableObject.hpp"
#include "Resource.hpp"
#include "Color.hpp"

CORE_BEGIN_NAMESPACE
class CORE_DLLREQ Sprite : public DrawableObject, public Resource
{
public:
	Sprite(){}
	virtual ~Sprite(){}

	virtual Resource	*clone() const {return const_cast<Sprite *>(this);}
	virtual void	draw(double /*elapsedTime*/ = 0){}
	virtual void	draw(int /*x*/, int /*y*/, double /*elapsedTime*/ = 0){}

	// setter
	virtual void	setTransparency(float){}
	virtual void	setColor(int /*r*/, int /*g*/, int /*b*/){}
	virtual void	setColor(Color const & /*color*/){}
	virtual void	setScale(float /*x*/, float /*y*/){}
	virtual void	setSpeed(double){}
	virtual void	setRepeat(bool){}
	virtual void	setPingpong(bool){}
	virtual void	setUp(bool){}
	virtual void	setTranslate(int /*x*/, int /*y*/){}
	virtual void	setGrid(uint32_t /*top*/, uint32_t /*left*/,
							uint32_t /*width*/, uint32_t /*height*/,
							uint32_t /*nbx*/, uint32_t /*nby*/,
							uint32_t /*spacex*/, uint32_t /*spacey*/){}
	virtual void	setBack(bool /*val*/){}
	virtual void	setVanish(bool) {}
	virtual void	setRotation(double) {}
	virtual void	rotate(double) {}
	virtual void	setCenter(double, double) {}
	virtual void	setCenter() {}

	// getter
	virtual int		getWidth() const { return 0; }
	virtual int		getHeight() const { return 0; }
	virtual int		getColor(int /*i*/) const { return 0; }
	virtual double	getRotation() const { return 0; }
	virtual bool	isFinished() const { return 0; }
};
CORE_END_NAMESPACE
