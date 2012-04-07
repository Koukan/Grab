#include "BlackHole.hpp"
#include "CircleHitBox.hpp"

BlackHole::BlackHole(double x, double y, Core::GameState &gameState)
	: ConcreteObject(""/*"blackHole"*/, *(new Core::CircleHitBox(x, y, 500)), 0, 0, -500, -500), _gameState(gameState), _elapsedTime(0), _angle(0), _nbParticles(500)
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
		obj = new ConcreteObject("blackHoleParticle", *(new Core::CircleHitBox(this->_x + ::cos(angle * 3.14 / 180), this->_y + ::sin(angle * 3.14 / 180), 5)),
			::cos((angle + 45) * 3.14 / 180) * 300, ::sin((angle + 45) * 3.14 / 180) * 300, -5, -5);
		this->_gameState.addGameObject(obj, "particles");
	}
	this->_particles.push_front(obj);
}

void BlackHole::draw(double elapsedTime)
{
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