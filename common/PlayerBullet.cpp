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
		  : Core::BulletCommand(parser, gstate, x, y, vx, vy), _groupName(groupName), _isFiring(true), _isConcentrated(false)
{
	this->setFocus("monster");
}

PlayerBullet::PlayerBullet(BulletMLState &state, Core::GameState &gstate, std::string const &groupName,
	double x, double y, double vx, double vy)
	: Core::BulletCommand(state, gstate, x, y, vx, vy), _groupName(groupName), _isFiring(true), _isConcentrated(false)
{
	this->setSprite(gstate, "playershot");
	this->setFocus("monster");
}

PlayerBullet::PlayerBullet(BulletMLState &state, Core::GameState &gstate, Core::HitBox &box, std::string const &groupName,
	double vx, double vy, double xHitboxOffset, double yHitboxOffset)
	: Core::BulletCommand(state, gstate, box, vx, vy, xHitboxOffset, yHitboxOffset), _groupName(groupName),
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
		if (direction < /*180*/270)
			direction = (direction + 3 * 90) / 4;
		else
			direction = (direction + 3 * /*270*/(360 + 90)) / 4;
		speed *= 1.2;
	}

	double		dir = dtor(direction);
	Bullet		*bullet;

	Core::HitBox		*box = new Core::CircleHitBox(_x, _y, 4);
	//if (_shape == Core::BulletCommand::Circle)
		//box = new Core::CircleHitBox(_x, _y,
			//static_cast<double>(_width));
	//else if (_shape == Core::BulletCommand::Rectangle)
		//box = new Core::RectHitBox(_x, _y,
			//static_cast<double>(_width),
			//static_cast<double>(_height));
	vx = speed * cos(dir);
	vy = -speed * sin(dir);
	//if (box)
	//{
	bullet = new Core::Bullet(_state, "playershot", *box, vx, vy, 0, 0);
	if (bullet->getSprite())
		bullet->getSprite()->setColor(_colors[0], _colors[1], _colors[2]);
	this->_state.addGameObject(bullet, this->_groupName/*this->_simpleGroup*/);
	this->insertChild(*bullet);
		//}
}

void	PlayerBullet::createBullet(BulletMLState* state, double direction, double speed)
{
	double			vx, vy;

	if (this->_isConcentrated)
	{
		if (direction < /*180*/270)
			direction = (direction + 3 * 90) / 4;
		else
			direction = (direction + 3 * /*270*/(360 + 90)) / 4;
		speed *= 1.2;
	}

	double			dir = dtor(direction);
	PlayerBullet	*bullet;

	Core::HitBox		*box = new Core::CircleHitBox(_x, _y, 4);
	//if (state->getShape() == "circle")
		//box = new Core::CircleHitBox(_x, _y,
			//static_cast<double>(state->getRadius()));
	//else if (state->getShape() == "rectangle")
		//box = new Core::RectHitBox(_x, _y,
			//static_cast<double>(state->getWidth()),
			//static_cast<double>(state->getHeight()));
	vx = speed * cos(dir);
	vy = -speed * sin(dir);
	//if (box)
	//{
	bullet = new PlayerBullet(*state, _state, *box, this->_groupName, vx, vy, state->getHitboxX(), state->getHitboxY());
	if (bullet->getSprite())
		bullet->getSprite()->setColor(_colors[0], _colors[1], _colors[2]);
	bullet->setColor(_colors[0], _colors[1], _colors[2]);
	this->_state.addGameObject(bullet, this->_groupName);
	this->insertChild(*bullet);
	bullet->setSeed(this->_rand());
	//}
	//else
	//{
		//bullet = new PlayerBullet(*state, _state, this->_groupName, _x, _y, vx, vy);
		//if (bullet->getSprite())
		  //bullet->getSprite()->setColor(_colors[0], _colors[1], _colors[2]);
		//bullet->setColor(_colors[0], _colors[1], _colors[2]);
		//this->_state.addGameObject(bullet, this->_groupName);
		//this->insertChild(*bullet);
		//bullet->setSeed(this->_rand());
	//}
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
			_turn += time * 100;
		else
			_turn += time * 50;
		this->run();
	}
	if (!this->_end)
		PhysicObject::move(time);
	else
		this->erase();
}

void	PlayerBullet::isFiring(bool firing)
{
	if (firing)
		this->_isFiring = true;
	else
	{
		this->_isFiring = false;
		this->_turn = 0;
	}
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
