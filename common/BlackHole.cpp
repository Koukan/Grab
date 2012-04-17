#include "BlackHole.hpp"
#include "CircleHitBox.hpp"
#include "Ship.hpp"
#include <cmath>

std::string const BlackHole::tab[2] = {"blackHoleParticle", "blackHoleParticle2"};


BlackHole::BlackHole(double x, double y, Core::GameState &gameState, Ship &ship)
	: ConcreteObject(""/*"blackHole"*/, *(new Core::CircleHitBox(x, y, 500)), 0, 0, -500, -500),
	_gameState(gameState), _elapsedTime(0), _elapsedTime2(15000), _angle(0), _nbParticles(500), _end(0), _ship(ship), _i(0)
{
	this->_gameState.addGameObject(this, "blackHoles");
}

BlackHole::~BlackHole()
{
}

void	BlackHole::createParticle(int angle)
{
	ConcreteObject *obj;
	if (this->_particles.size() == this->_nbParticles)
	{
		obj = this->_particles.back();
		this->_particles.pop_back();
		obj->setX(this->_x + ::cos(angle * 3.14 / 180));
		obj->setY(this->_y + ::sin(angle * 3.14 / 180));
		obj->setVx(::cos((angle + 45) * 3.14 / 180) * 300);
		obj->setVy(::sin((angle + 45) * 3.14 / 180) * 300);
		obj->setAx(0);
		obj->setAy(0);
	}
	else
	{
		obj = new ConcreteObject(BlackHole::tab[_i], *(new Core::CircleHitBox(this->_x + ::cos(angle * 3.14 / 180), this->_y + ::sin(angle * 3.14 / 180), 5)),
			::cos((angle + 45) * 3.14 / 180) * 300, ::sin((angle + 45) * 3.14 / 180) * 300, -5, -5);
		this->_gameState.addGameObject(obj, "particles");
		_i = (_i + 1) % 2;
	}
	this->_particles.push_front(obj);
}

void BlackHole::draw(double elapsedTime)
{
	if (this->_elapsedTime2 <= 0)
	{
		if (!this->_end)
		{
			this->_end = new ConcreteObject("", *(new Core::CircleHitBox(this->_x, this->_y, 200)), 0, 0, -200, -200);
			this->_gameState.addGameObject(this->_end, "blackHoleEnd");
		}
		else
		{
			this->_end->erase();
			this->erase();
			this->_ship.setSpecialPowerActive(false);
			return ;
		}
		this->_elapsedTime2 += 500;
	}
	else
	{
		this->_elapsedTime2 -= elapsedTime;
		if (this->_elapsedTime <= 0)
		{
			this->createParticle(this->_angle);
			this->createParticle(this->_angle + 180);
			this->createParticle(this->_angle + 90);
			this->createParticle(this->_angle + 180 + 90);
			this->_angle = (this->_angle + 20) % 360;
			this->_elapsedTime += 100;
		}
		else
			this->_elapsedTime -= elapsedTime;
		this->ConcreteObject::draw(elapsedTime);
	}
}

bool	BlackHole::isEnd() const
{
	return (this->_end != 0);
}
