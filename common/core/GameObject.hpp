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
	GameObject(double x = 0, double y = 0, double z = 0, Group *group = 0);
	virtual ~GameObject();

	// setter
	void				setId(uint32_t id);
	virtual void		setX(double x);
	virtual void		setY(double y);
	virtual void		setPosition(double x, double y, double z = 0);
	void				setGroup(Group *group);
	void				setRelativeObject(GameObject *obj);

	// getter
	uint32_t			getId() const;
	double				getX() const;
	double				getY() const;
	Group				*getGroup() const;
	int8_t				isDelete() const;
	GameObject			*getRelativeObject() const;

	virtual void		erase();

protected:
	void				addGameObject(GameObject &obj);
	void				removeGameObject(GameObject &obj);

	double					_x;
	double 					_y;
	double					_z;
	int8_t					_delete;
	uint32_t				_id;
	Group					*_group;
	GameObject				*_relativeObject;
	std::list<GameObject*>	_objects;

private:
	void				removeGroup();

	friend class GameObjectManager;
};

CORE_END_NAMESPACE
