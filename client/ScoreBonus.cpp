#include "ScoreBonus.hpp"

ScoreBonus::ScoreBonus(std::string const& spriteName, unsigned int score,
		       Core::HitBox& hitbox, double vx, double vy,
		       double xHitBoxOffset, double yHitBoxOffset) :
  ConcreteObject(spriteName, hitbox, vx, vy, xHitBoxOffset, yHitBoxOffset),
  score(score)
{}

ScoreBonus::~ScoreBonus()
{}

