#pragma once

#include <stdint.h>
#include <cstdlib>
#include "Net.hpp"
#include "CoreDef.hpp"

CORE_BEGIN_NAMESPACE

class GameObjectManager;
class Group;

class CORE_DLLREQ GameObject : public Net::PoolObject
{
public:
	GameObject(double x = 0, double y = 0, Group *group = 0);
	virtual ~GameObject();

	// setter
	void				setId(uint32_t id);
	virtual void		setX(double x);
	virtual void		setY(double y);
	virtual void		setPosition(double x, double y);
	void				setGroup(Group *group);

	// getter
	uint32_t	getId() const;
	double		getX() const;
	double		getY() const;
	Group		*getGroup() const;
	bool		isDelete() const;

	void		erase();

protected:
	double			_x;
	double 			_y;
	bool			_delete;
	uint32_t		_id;
	Group			*_group;

	friend class GameObjectManager;
};

CORE_END_NAMESPACE
