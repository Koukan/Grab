#pragma once

#include "BulletCommand.hpp"

class PlayerBullet : public Core::BulletCommand
{
public:
	PlayerBullet(std::string const &parser, Core::GameState &gstate, std::string const &groupName,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    PlayerBullet(BulletMLState &state, Core::GameState &gstate, std::string const &groupName,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    PlayerBullet(BulletMLState &state, Core::GameState &gstate, Core::HitBox &box, std::string const &groupName,
		  double vx = 0, double vy = 0);
	~PlayerBullet();

	void			isFiring(bool firing);

    virtual void	doAccelY(double speedy);
    virtual void	createBullet(BulletMLState* state, double direction, double speed);
    virtual void	move(double time);

private:
	std::string const _groupName;
	bool			_isFiring;
};
