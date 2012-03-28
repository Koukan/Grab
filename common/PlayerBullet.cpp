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
		  : Core::BulletCommand(parser, gstate, x, y, vx, vy), _groupName(groupName), _isFiring(false), _isConcentrated(false)
{
	this->setFocus("monster");
}

PlayerBullet::PlayerBullet(BulletMLState &state, Core::GameState &gstate, std::string const &groupName,
	double x, double y, double vx, double vy)
	: Core::BulletCommand(state, gstate, false, x, y, vx, vy), _groupName(groupName), _isFiring(true), _isConcentrated(false)
{
	this->setSprite(gstate, "playershot");
	this->setFocus("monster");
}

PlayerBullet::PlayerBullet(BulletMLState &state, Core::GameState &gstate, Core::HitBox &box, std::string const &groupName,
	double vx, double vy, double xHitboxOffset, double yHitboxOffset)
	: Core::BulletCommand(state, gstate, box, false, vx, vy, xHitboxOffset, yHitboxOffset), _groupName(groupName),
	_isFiring(true), _isConcentrated(false)
{
	this->setSprite(gstate, "playershot");
	this->setFocus("monster");
}

PlayerBullet::~PlayerBullet()
{
}

void	PlayerBullet::createSimpleBullet(double direction, double speed)
{
	double		vx, vy;

	if (this->_isConcentrated)
	{
		if (direction <= 20)
			direction = direction / 3;
		else if (direction >= 340)
			direction = ((direction - 360) / 3) + 360;
		else if (direction >= 160 && direction <= 200)
			direction = ((direction - 180) / 3) + 180;
		else if (direction < /*180*/270)
			direction = (direction + 3 * 90) / 4;
		else
			direction = (direction + 3 * /*270*/(360 + 90)) / 4;
		speed *= 1.2;
	}

	double		dir = dtor(direction);
	Bullet		*bullet;

	Core::HitBox		*box = new Core::CircleHitBox(_x, _y, 4);
	vx = speed * cos(dir);
	vy = -speed * sin(dir);
	bullet = new Core::Bullet(_state, "playershot", *box, vx, vy, 0, 0);
	bullet->setXHitBoxOffset(-4);
	bullet->setYHitBoxOffset(-4);
	if (bullet->getSprite())
		bullet->getSprite()->setColor(_colors[0], _colors[1], _colors[2]);
	this->_state.addGameObject(bullet, this->_groupName/*this->_simpleGroup*/);
}

void	PlayerBullet::createBullet(BulletMLState* state, double direction, double speed)
{
	double			vx, vy;

	if (this->_isConcentrated)
	{
		if (direction <= 20)
			direction = direction / 3;
		else if (direction >= 340)
			direction = ((direction - 360) / 3) + 360;
		else if (direction >= 160 && direction <= 200)
			direction = ((direction - 180) / 3) + 180;
		else if (direction < /*180*/270)
			direction = (direction + 3 * 90) / 4;
		else
			direction = (direction + 3 * /*270*/(360 + 90)) / 4;
		speed *= 1.2;
	}

	double			dir = dtor(direction);
	PlayerBullet	*bullet;

	Core::HitBox		*box = new Core::CircleHitBox(_x, _y, 4);
	vx = speed * cos(dir);
	vy = -speed * sin(dir);
	bullet = new PlayerBullet(*state, _state, *box, this->_groupName, vx, vy, state->getHitboxX(), state->getHitboxY());
	bullet->setXHitBoxOffset(-4);
	bullet->setYHitBoxOffset(-4);
	if (bullet->getSprite())
		bullet->getSprite()->setColor(_colors[0], _colors[1], _colors[2]);
	bullet->setColor(_colors[0], _colors[1], _colors[2]);
	this->_state.addGameObject(bullet, this->_groupName);
	bullet->setSeed(this->_rand());
	delete state;
}

double	PlayerBullet::getAimDirection()
{
	double	tmp = this->BulletCommand::getAimDirection();

	if (!this->_relativeObject)
		return 270;
	return tmp;
}

void	PlayerBullet::move(double time)
{
	if (this->_isFiring)
	{
		if (this->_isConcentrated)
			_turn += time * 75;
		else
			_turn += time * 50;
		this->run();
	}
	else if (_turn != 0)
		this->run();

	if (!this->_end)
		PhysicObject::move(time);
	else
		this->erase();
}

void	PlayerBullet::isFiring(bool firing)
{
	this->_isFiring = firing;
}

void	PlayerBullet::setColor(uint8_t r, uint8_t g, uint8_t b)
{
	_colors[0] = r;
	_colors[1] = g;
	_colors[2] = b;
}

void	PlayerBullet::isConcentrated(bool concentrated)
{
	this->_isConcentrated = concentrated;
}

bool	PlayerBullet::isConcentrated() const
{
	return (this->_isConcentrated);
}
