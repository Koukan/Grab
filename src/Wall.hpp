#pragma once

#include <string>
#include "PhysicObject.hpp"

class Wall : public PhysicObject
{
public:
	Wall(double x, double y, double width, double height, std::string const &groupName = "walls");
	virtual ~Wall();

	void			collideBullet(GameObject &);
	virtual void	draw(double);
};

