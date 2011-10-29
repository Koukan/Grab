#pragma once

#include "bulletmlrunner.h"
#include "Sprite.hpp"
#include "PhysicObject.hpp"
#include "Game.hpp"
#include "Bullet.hpp"

class BulletCommand : public BulletMLRunner, public Bullet
{
  public:
    BulletCommand(BulletMLParser* parser, GameState &gstate, std::string const &sprite,
		  double x = 0, double y = 0, double direction = 0, double speed = 0);
    BulletCommand(BulletMLState* state, GameState &gstate, std::string const &sprite,
		  double x = 0, double y = 0, double direction = 0, double speed = 0);
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
    virtual void	move(int time);

  private:
    double		_turn;
    GameState		&_state;
};
