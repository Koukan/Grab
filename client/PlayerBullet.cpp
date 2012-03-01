#include <math.h>
#include "PlayerBullet.hpp"
#include "RectHitBox.hpp"
#include "CircleHitBox.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline static double dtor(double x) { return x * M_PI / 180; }
inline static double rtod(double x) { return x * 180 / M_PI; }

PlayerBullet::PlayerBullet(std::string const &parser, Core::GameState &gstate, std::string const &groupName,
		  double x, double y, double vx, double vy)
		  : Core::BulletCommand(parser, gstate, x, y, vx, vy), _groupName(groupName), _isFiring(false)
{
}

PlayerBullet::PlayerBullet(BulletMLState &state, Core::GameState &gstate, std::string const &groupName,
	double x, double y, double vx, double vy)
	: Core::BulletCommand(state, gstate, x, y, vx, vy), _groupName(groupName), _isFiring(false)
{
}

PlayerBullet::PlayerBullet(BulletMLState &state, Core::GameState &gstate, Core::HitBox &box, std::string const &groupName,
	double vx, double vy)
	: Core::BulletCommand(state, gstate, box, vx, vy), _groupName(groupName), _isFiring(false)
{
}

PlayerBullet::~PlayerBullet()
{
}

void	PlayerBullet::doAccelY(double speedy)
{
	this->_vy = -speedy;
	this->setSpeedDirection();
}

void	PlayerBullet::createBullet(BulletMLState* state, double direction, double speed)
{
	Core::HitBox			*box = 0;
	double			vx, vy;
	double			dir = dtor(direction);
	Core::BulletCommand	*bullet;

	if (state->getShape() == "circle")
		box = new Core::CircleHitBox(_x, _y,
			static_cast<double>(state->getRadius()));
	else if (state->getShape() == "rectangle")
		box = new Core::RectHitBox(_x, _y,
			static_cast<double>(state->getWidth()),
			static_cast<double>(state->getHeight()));
	vx = speed * cos(dir);
	vy = -speed * sin(dir);
	if (box)
	{
		bullet = new PlayerBullet(*state, _state, *box, this->_groupName, vx, vy);
		this->_state.addGameObject(bullet, this->_groupName);
		this->insertChild(*bullet);
		bullet->setSeed(this->_rand());
	}
	else
	{
		bullet = new PlayerBullet(*state, _state, this->_groupName, _x, _y, vx, vy);
		this->_state.addGameObject(bullet, this->_groupName);
		this->insertChild(*bullet);
		bullet->setSeed(this->_rand());
	}
	delete state;
}

void		PlayerBullet::move(double time)
{
	if (this->_isFiring)
	{
		_turn += time * 50;
		this->run();
	}
	if (!this->_end)
		PhysicObject::move(time);
	else
		this->erase();
}

void			PlayerBullet::isFiring(bool firing)
{
	if (firing)
		this->_isFiring = true;
	else
	{
		this->_isFiring = false;
		this->_turn = 0;
	}
}
