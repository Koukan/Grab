#pragma once
//#include "ConcreteObject.hpp"
#include "BulletCommand.hpp"

class ScoreBonus : public /*ConcreteObject*/Core::BulletCommand
{
public:
  ScoreBonus(unsigned int score, double x, double y, std::string const& scriptName, Core::GameState &gameState/*std::string const& spriteName, unsigned int score,
	     Core::HitBox& hitbox, double vx = 0, double vy = 0,
	     double xHitBoxOffset = 0, double yHitBoxOffset = 0*/);

    ScoreBonus(int score, BulletMLState &state, Core::GameState &gstate, bool paused,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    ScoreBonus(int score, BulletMLState &state, Core::GameState &gstate, Core::HitBox &box, bool paused,
		  double vx = 0, double vy = 0, double xHitboxOffset = 0, double yHitboxOffset = 0);
	~ScoreBonus();

    virtual void	createBullet(BulletMLState* state, double direction, double speed);
	unsigned int const	score;
};
