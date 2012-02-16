#pragma once

#include <string>
#include "PhysicObject.hpp"

class Wall : public Core::PhysicObject
{
public:
	Wall(double x, double y, double width, double height, std::string const &groupName = "walls");
	virtual ~Wall();

  void			collideBullet(Core::GameObject &);
	virtual void	draw(double);
};

