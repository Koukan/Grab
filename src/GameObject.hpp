#pragma once

class GameObjectManager;
class Group;

class GameObject
{
public:
	GameObject(double x = 0, double y = 0, Group *group = 0);
	virtual ~GameObject(void);

	// setter
	virtual void		setX(double x);
	virtual void		setY(double y);
	virtual void		setPosition(double x, double y);
	void					setGroup(Group *group);

	// getter
	double		getX() const;
	double		getY() const;
	Group		*getGroup() const;

protected:
	double			_x;
	double 			_y;
	Group			*_group;
};
