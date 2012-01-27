#pragma once

#include "BulletCommand.hpp"

class BCommand : public BulletCommand
{
  public:
    BCommand(std::string const &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, int life = 0);
    BCommand(BulletMLParser &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, int life = 0);
    BCommand(BulletMLState &state, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, int life = 0);
    BCommand(BulletMLState &state, GameState &gstate, HitBox &box,
		  double vx = 0, double vy = 0, int life = 0);
    virtual ~BCommand();

	virtual void	createSimpleBullet(double direction, double speed);
	virtual void	createBullet(BulletMLState *state, double direction,
								 double speed);
	virtual void	move(double time);

	int			getLife() const;
	void		setLife(int life);
  private:
	double		_elapsedTime;
	int			_life;
};
