#pragma once

#include "GameObjectManager.hpp"

class GameObject
{
public:
	GameObject(double x = 0, double y = 0, Group *group = 0);
	virtual ~GameObject(void);

	double		getX() const;
	double		getY() const;
	Group		*getGroup() const;

	void		setX(double x);
	void		setY(double y);
	void		setGroup(Group *group);

protected:
	double			_x;
	double 			_y;
	Group			*_group;
};
