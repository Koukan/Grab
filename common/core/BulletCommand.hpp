#pragma once

#include "bulletmlrunner.h"
#include "Sprite.hpp"
#include "PhysicObject.hpp"
#include "Bullet.hpp"
#include "GameState.hpp"

class BulletCommand : public BulletMLRunner, public Bullet
{
  public:
    BulletCommand(std::string const &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    BulletCommand(BulletMLParser &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    BulletCommand(BulletMLState &state, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    BulletCommand(BulletMLState &state, GameState &gstate, HitBox &box,
		  double vx = 0, double vy = 0);
    virtual ~BulletCommand();
    virtual double	getBulletDirection();
    virtual double	getAimDirection();
    virtual double	getBulletSpeed();
    virtual double	getDefaultSpeed();
    virtual double	getRank();
    virtual void	createSimpleBullet(double direction, double speed);
    virtual void	createBullet(BulletMLState* state,
		    		     double direction, double speed);
    virtual int		getTurn();
    virtual void	doVanish();
    virtual void	doChangeDirection(double direction);
    virtual void	doChangeSpeed(double speed);
    virtual void	doAccelX(double speedx);
    virtual void	doAccelY(double speedy);
    virtual double	getBulletSpeedX();
    virtual double	getBulletSpeedY();
    virtual void	move(double time);

  protected:
	enum		Shape
	{
		Circle,
		Rectangle
	};

	void			setSpeedDirection();

	double			_direction;
	double			_speed;
    double			_turn;
    bool			_end;
    GameState		&_state;
	Shape			_shape;
	uint32_t		_width;
	uint32_t		_height;
	std::string		_simpleSprite;
	std::string		_simpleGroup;
};
