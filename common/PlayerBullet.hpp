#pragma once

#include "BulletCommand.hpp"

class PlayerBullet : public Core::BulletCommand
{
public:
	PlayerBullet(std::string const &parser, Core::GameState &gstate, std::string const &groupName,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, int angle = 0, PhysicObject *relativeObject = 0, PhysicObject::Constraint constraint = PhysicObject::NONE);
    PlayerBullet(BulletMLState &state, Core::GameState &gstate, std::string const &groupName,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, int angle = 0, PhysicObject *relativeObject = 0, PhysicObject::Constraint constraint = PhysicObject::NONE);
    PlayerBullet(BulletMLState &state, Core::GameState &gstate, Core::HitBox &box, std::string const &groupName,
		  double vx = 0, double vy = 0, double xHitboxOffset = 0, double yHitboxOffset = 0, int angle = 0, PhysicObject *relativeObject = 0,
		  PhysicObject::Constraint constraint = PhysicObject::ALL);
	~PlayerBullet();

	void			isFiring(bool firing);

    virtual void	createSimpleBullet(double direction, double speed);
    virtual void	createBullet(BulletMLState* state, double direction, double speed);
	virtual double	getAimDirection();
    virtual void	move(double time);
	virtual void	erase();
	void			setColor(uint8_t r, uint8_t g, uint8_t b);
	void			isConcentrated(bool concentrated);
	bool			isConcentrated() const;

private:
	std::string const	_groupName;
	bool				_isFiring;
	bool				_isConcentrated;
	int					_angle;
	uint8_t				_colors[3];
	PhysicObject		*_relative;
	PhysicObject::Constraint	_constraint;
};
