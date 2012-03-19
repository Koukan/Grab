#pragma once
#include "ConcreteObject.hpp"

class ScoreBonus : public ConcreteObject
{
public:
  ScoreBonus(std::string const& spriteName, unsigned int score,
	     Core::HitBox& hitbox, double vx = 0, double vy = 0,
	     double xHitBoxOffset = 0, double yHitBoxOffset = 0);
  ~ScoreBonus();

  unsigned int const	score;
};
