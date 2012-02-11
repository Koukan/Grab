#pragma once

#include <stdint.h>
#include "DrawableObject.hpp"
#include "Resource.hpp"

class Sprite : public DrawableObject, public Resource
{
public:
	Sprite(){}
	virtual ~Sprite(){}

	virtual Resource	*clone() const {return const_cast<Sprite *>(this);}
	virtual void	draw(double /*elapsedTime*/ = 0){}
	virtual void	draw(int /*x*/, int /*y*/, double /*elapsedTime*/ = 0){}

	// setter
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

	// getter
	virtual int		getWidth() const { return 0; }
	virtual int		getHeight() const { return 0; }
};
