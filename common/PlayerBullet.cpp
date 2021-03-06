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
		  double x, double y, double vx, double vy, int angle, PhysicObject *relativeObject, PhysicObject::Constraint constraint)
		  : Core::BulletCommand(parser, gstate, x, y, vx, vy), _groupName(groupName), _isFiring(false), _isConcentrated(false), _angle(angle), _relative(relativeObject),
		  _constraint(constraint)
{
	this->removeFocus("players");
	this->addFocus("monster");
	this->addFocus("monster2");
}

PlayerBullet::PlayerBullet(BulletMLState &state, Core::GameState &gstate, std::string const &groupName,
	double x, double y, double vx, double vy, int angle, PhysicObject *relativeObject, PhysicObject::Constraint constraint)
	: Core::BulletCommand(state, gstate, false, x, y, vx, vy), _groupName(groupName), _isFiring(true), _isConcentrated(false), _angle(angle), _relative(relativeObject),
	_constraint(constraint)
{
	if (!this->getSprite())
		this->setSprite(gstate, "playershot");
	this->setSprite(gstate, "playershot");
	this->removeFocus("players");
	this->addFocus("monster");
	this->addFocus("monster2");
}

PlayerBullet::PlayerBullet(BulletMLState &state, Core::GameState &gstate, Core::HitBox &box, std::string const &groupName,
	double vx, double vy, double xHitboxOffset, double yHitboxOffset, int angle, PhysicObject *relativeObject, PhysicObject::Constraint constraint)
	: Core::BulletCommand(state, gstate, box, false, vx, vy, xHitboxOffset, yHitboxOffset), _groupName(groupName),
	_isFiring(true), _isConcentrated(false), _angle(angle), _relative(relativeObject),
	_constraint(constraint)
{
	if (!this->getSprite())
		this->setSprite(gstate, "playershot");
	this->setSprite(gstate, "playershot");
	this->removeFocus("players");
	this->addFocus("monster");
	this->addFocus("monster2");
}

PlayerBullet::~PlayerBullet()
{
}

void	PlayerBullet::createSimpleBullet(double direction, double speed)
{
	double		vx, vy;
	if (this->_isConcentrated)
	{
		if (direction < 270)
			direction = (direction + 3 * 90) / 4;
		else
			direction = (direction + 3 * (360 + 90)) / 4;
		speed *= 1.2;
	}
	direction += this->_angle;

	double		dir = dtor(direction);
	Bullet		*bullet;

	Core::HitBox		*box = new Core::CircleHitBox(this->getX(), this->getY(), 4);
	vx = speed * cos(dir);
	vy = speed * sin(dir);
	if (this->_simpleSprite == "")
		bullet = new Core::Bullet(_state, "playershot", *box, vx, vy, 0, 0);
	else
		bullet = new Core::Bullet(_state, this->_simpleSprite, *box, vx, vy, 0, 0);
	if ((this->_constraint & PhysicObject::X) != 0)
		bullet->setX(0);
	if ((this->_constraint & PhysicObject::Y) != 0)
		bullet->setY(0);
	if (this->_constraint != Core::PhysicObject::NONE)
		bullet->setLink(this->_relative, this->_constraint);
	bullet->setXHitBoxOffset(-4);
	bullet->setYHitBoxOffset(-4);
	if (bullet->getSprite())
	{
		bullet->getSprite()->setTransparency(0.35);
		bullet->getSprite()->setColor(_colors[0], _colors[1], _colors[2]);
	}
	if (this->_simpleGroup == "")
		this->_state.addGameObject(bullet, this->_groupName);
	else
		this->_state.addGameObject(bullet, this->_simpleGroup);
}

void	PlayerBullet::createBullet(BulletMLState* state, double direction, double speed)
{
	double			vx, vy;

	if (this->_isConcentrated)
	{
		if (direction < 270)
			direction = (direction + 3 * 90) / 4;
		else
			direction = (direction + 3 * (360 + 90)) / 4;
		speed *= 1.2;
	}
	direction += this->_angle;

	double			dir = dtor(direction);
	PlayerBullet	*bullet;

	Core::HitBox		*box = new Core::CircleHitBox(this->getX(), this->getY(), 4);
	vx = speed * cos(dir);
	vy = speed * sin(dir);
	bullet = new PlayerBullet(*state, _state, *box, this->_groupName, vx, vy, state->getHitboxX(), state->getHitboxY(), this->_angle, this->_relative, this->_constraint);
	if ((this->_constraint & PhysicObject::X) != 0)
		bullet->setX(0);
	if ((this->_constraint & PhysicObject::Y) != 0)
		bullet->setY(0);
	if (this->_constraint != Core::PhysicObject::NONE)
		bullet->setLink(this->_relative, this->_constraint);
	bullet->setXHitBoxOffset(-4);
	bullet->setYHitBoxOffset(-4);
	if (bullet->getSprite())
	{
		bullet->getSprite()->setColor(_colors[0], _colors[1], _colors[2]);
		bullet->getSprite()->setTransparency(0.35);
	}
	bullet->setColor(_colors[0], _colors[1], _colors[2]);
	if (state->getGroup() == "")
		this->_state.addGameObject(bullet, this->_groupName);
	else
		this->_state.addGameObject(bullet, state->getGroup());
	bullet->setSeed(this->_rand());
	delete state;
}

double	PlayerBullet::getAimDirection()
{
	return this->BulletCommand::getAimDirection(270);
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

void	PlayerBullet::erase()
{
	if (!this->_delete && !this->_deathBullet.empty())
	{
		PlayerBullet	*bullet = new PlayerBullet(this->_deathBullet, _state,
									"playerShots", this->getX(), this->getY(), 0, 0, this->_angle, this->_relative, this->_constraint);
		bullet->setColor(this->_colors[0], this->_colors[1], this->_colors[2]);
		bullet->isFiring(true);
		//BulletCommand	*bullet = new BulletCommand(this->_deathBullet, _state, this->getX(), this->getY(), _vx, _vy);
		//bullet->setScrollY(this->_scrollY);
		this->_state.addGameObject(bullet, "spawner", false);
		this->insertChild(*bullet);
		bullet->setSeed(this->_rand());
		bullet->setRank(this->_rank);
	}
	this->GameObject::erase();
	if (this->_childs.empty())
	{
		if (this->_parent)
			this->_parent->removeChild(this->_bulletId);
	}
	else
		this->_delete = 2;
}
