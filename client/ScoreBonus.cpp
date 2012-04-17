#include "ScoreBonus.hpp"
#include "CircleHitBox.hpp"
#include "RectHitBox.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline static double dtor(double x) { return x * M_PI / 180.0; }
inline static double rtod(double x) { return x * 180.0 / M_PI; }

ScoreBonus::ScoreBonus(unsigned int score, double x, double y, std::string const& scriptName, Core::GameState &gameState) :
  Core::BulletCommand(scriptName, gameState, x, y),
  score(score)
{
}

ScoreBonus::ScoreBonus(int score, BulletMLState &state, Core::GameState &gstate, bool paused,
		double x, double y, double vx, double vy)
	: Core::BulletCommand(state, gstate, paused, x, y, vx, vy), score(score)
{
}

ScoreBonus::ScoreBonus(int score, BulletMLState &state, Core::GameState &gstate,
			     Core::HitBox &box, bool paused,
			     double vx, double vy, double xHitboxOffset, double yHitboxOffset)
	: Core::BulletCommand(state, gstate, box, paused, vx, vy, xHitboxOffset, yHitboxOffset), score(score)
{
}

ScoreBonus::~ScoreBonus()
{}

void		ScoreBonus::createBullet(BulletMLState* state,
				  	    double direction, double speed)
{
	Core::HitBox			*box = 0;
	double			vx, vy;
	double			dir = dtor(direction);
	BulletCommand	*bullet = 0;

	if (state->getShape() == "circle")
		box = new Core::CircleHitBox(this->getX(), this->getY(),
			static_cast<double>(state->getRadius()));
	else if (state->getShape() == "rectangle")
		box = new Core::RectHitBox(this->getX(), this->getY(),
			static_cast<double>(state->getWidth()),
			static_cast<double>(state->getHeight()));
	vx = speed * cos(dir);
	vy = speed * sin(dir);
	if (box)
	{
		bullet = new ScoreBonus(this->score, *state, _state, *box, _paused, vx, vy, state->getHitboxX(), state->getHitboxY());
		bullet->setScrollY(this->_scrollY);
		this->_state.addGameObject(bullet, state->getGroup(), false);
		this->insertChild(*bullet);
		bullet->setSeed(this->_rand());
		bullet->setRank(this->_rank);
	}
	else
	{
		bullet = new ScoreBonus(this->score, *state, _state, _paused, this->getX(), this->getY(), vx, vy);
		bullet->setScrollY(this->_scrollY);
		this->_state.addGameObject(bullet, state->getGroup(), false);
		this->insertChild(*bullet);
		bullet->setSeed(this->_rand());
		bullet->setRank(this->_rank);
	}
	delete state;
}
