#include <math.h>
#include "BulletCommand.hpp"
#include "Bullet.hpp"
#include "bulletmlparser.h"
#include "CircleHitBox.hpp"
#include "RectHitBox.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

CORE_USE_NAMESPACE

inline static double dtor(double x) { return x * M_PI / 180; }
inline static double rtod(double x) { return x * 180 / M_PI; }

BulletCommand::BulletCommand(std::string const &parser, GameState &gstate,
		double x, double y, double vx, double vy)
	: BulletMLRunner(gstate.getBulletParser(parser)), Bullet(x, y, vx, vy),
	  _direction(0), _speed(0), _turn(0), _end(false),
	  _state(gstate), _shape(BulletCommand::Circle),
	  _width(1), _height(1), _rank(0.5), _nextId(1)
{
	this->setSpeedDirection();
}

BulletCommand::BulletCommand(BulletMLParser &parser, GameState &gstate,
		double x, double y, double vx, double vy)
	: BulletMLRunner(&parser), Bullet(x, y, vx, vy),
	  _direction(0), _speed(0), _turn(0), _end(false),
	  _state(gstate), _shape(BulletCommand::Circle),
	  _width(1), _height(1), _rank(0.5), _nextId(1)
{
	this->setSpeedDirection();
}

BulletCommand::BulletCommand(BulletMLState &state, GameState &gstate,
		double x, double y, double vx, double vy)
	: BulletMLRunner(&state), Bullet(x, y, vx, vy),
	  _direction(0), _speed(0), _turn(0), _end(false), _state(gstate),
	  _width(state.getWidth()), _height(state.getHeight()), _rank(0.5),
	  _nextId(1)
{
	if (state.getShape() == "circle")
		this->_shape = BulletCommand::Circle;
	else if (state.getShape() == "rectangle")
		this->_shape = BulletCommand::Rectangle;
	if (!state.getSprite().empty())
		this->setSprite(_state, state.getSprite());
	this->_simpleSprite = state.getBulletSprite();
	this->_simpleGroup = state.getBulletGroup();
	this->setSpeedDirection();
}

BulletCommand::BulletCommand(BulletMLState &state, GameState &gstate,
		HitBox &box, double vx, double vy)
	: BulletMLRunner(&state), Bullet(box, vx, vy),
	  _direction(0), _speed(0), _turn(0), _end(false), _state(gstate),
	  _width(state.getWidth()), _height(state.getHeight()), _rank(0.5),
	  _nextId(1)
{
	if (state.getShape() == "circle")
		this->_shape = BulletCommand::Circle;
	else if (state.getShape() == "rectangle")
		this->_shape = BulletCommand::Rectangle;
	if (!state.getSprite().empty())
		this->setSprite(_state, state.getSprite());
	this->_simpleSprite = state.getBulletSprite();
	this->_simpleGroup = state.getBulletGroup();
	this->setSpeedDirection();
}

BulletCommand::~BulletCommand()
{
}

double		BulletCommand::getBulletDirection()
{
	return rtod(_direction);
}

double		BulletCommand::getAimDirection()
{
	return 0;
}

double		BulletCommand::getBulletSpeed()
{
	return this->_speed;
}

double		BulletCommand::getDefaultSpeed()
{
	return 1.0;
}

double		BulletCommand::getRank()
{
	return this->_rank;
}

double		BulletCommand::getRand()
{
	return this->_rand();
}

void		BulletCommand::createSimpleBullet(double direction, double speed)
{
	HitBox		*box = 0;
	double		vx, vy;
	double		dir = dtor(direction);
	Bullet		*bullet;

	if (_shape == BulletCommand::Circle)
		box = new CircleHitBox(_x, _y,
			static_cast<double>(_width));
	else if (_shape == BulletCommand::Rectangle)
		box = new RectHitBox(_x, _y,
			static_cast<double>(_width),
			static_cast<double>(_height));
	vx = speed * cos(dir);
	vy = speed * sin(dir);
	if (box)
	{
		bullet = new Bullet(_state, this->_simpleSprite, *box, vx, vy);
		this->_state.addGameObject(bullet, this->_simpleGroup);
		this->insertChild(*bullet);
	}
}

void		BulletCommand::createBullet(BulletMLState* state,
				  	    double direction, double speed)
{
	HitBox			*box = 0;
	double			vx, vy;
	double			dir = dtor(direction);
	BulletCommand	*bullet;

	if (state->getShape() == "circle")
		box = new CircleHitBox(_x, _y,
			static_cast<double>(state->getRadius()));
	else if (state->getShape() == "rectangle")
		box = new RectHitBox(_x, _y,
			static_cast<double>(state->getWidth()),
			static_cast<double>(state->getHeight()));
	vx = speed * cos(dir);
	vy = speed * sin(dir);
	if (box)
	{
		bullet = new BulletCommand(*state, _state, *box, vx, vy);
		this->_state.addGameObject(bullet, state->getGroup());
		this->insertChild(*bullet);
	}
	else
	{
		bullet = new BulletCommand(*state, _state, _x, _y, vx, vy);
		this->_state.addGameObject(bullet, state->getGroup());
		this->insertChild(*bullet);
	}
	delete state;
}

int			BulletCommand::getTurn()
{
	return static_cast<int>(_turn);
}

void		BulletCommand::doVanish()
{
	this->_end = true;
}

void		BulletCommand::doChangeDirection(double direction)
{
	this->_direction = dtor(direction);
	this->_vx = this->_speed * cos(this->_direction);
	this->_vy = this->_speed * sin(this->_direction);
}

void		BulletCommand::doChangeSpeed(double speed)
{
	this->_speed = speed;
	this->_vx = this->_speed * cos(this->_direction);
	this->_vy = this->_speed * sin(this->_direction);
}

void		BulletCommand::doAccelX(double speedx)
{
	this->_vx = speedx;
	this->setSpeedDirection();
}

void		BulletCommand::doAccelY(double speedy)
{
	this->_vy = speedy;
	this->setSpeedDirection();
}

double		BulletCommand::getBulletSpeedX()
{
	return this->_vx;
}

double		BulletCommand::getBulletSpeedY()
{
	return this->_vy;
}

void		BulletCommand::setRank(double rank)
{
	this->_rank = rank;
}

void		BulletCommand::move(double time)
{
	_turn += time * 50;
	this->run();
	if (!this->_end)
		PhysicObject::move(time);
	else
		this->erase();
}

void		BulletCommand::setSeed(uint32_t seed)
{
	this->_rand.seed(seed);
}

uint32_t	BulletCommand::getSeed() const
{
	return this->_rand.getSeed();
}

Bullet		*BulletCommand::getChild(uint32_t id) const
{
	BulletMap::const_iterator	it = this->_childs.find(id);

	if (it != this->_childs.end())
		return it->second;
	return 0;
}

void		BulletCommand::setSpeedDirection()
{
	this->_direction = atan2(this->_vy, this->_vx);
	this->_speed = sqrt(this->_vx * this->_vx + this->_vy * this->_vy);
}

void		BulletCommand::insertChild(Bullet &bullet)
{
	bullet.setBulletId(this->_nextId);
	bullet.setParent(this);
	this->_childs[this->_nextId++] = &bullet;
}
