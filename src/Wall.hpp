#pragma once

#include <string>
#include "PhysicObject.hpp"

class Wall : public PhysicObject
{
public:
	Wall(double x, double y, double width, double height, std::string const &groupName = "walls");
	~Wall(void);

	void	collideBullet(GameObject &);
};

