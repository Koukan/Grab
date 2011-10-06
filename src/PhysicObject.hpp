#pragma once

#include <list>
#include "GameObject.hpp"

class PhysicObject : public GameObject
{
public:
	PhysicObject(void);
	virtual ~PhysicObject(void);
	virtual bool	collide(PhysicObject &object);

protected:
	int		_vx;
	int		_vy;
};
