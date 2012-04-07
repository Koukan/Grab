#pragma once

#include "ConcreteObject.hpp"
#include "GameState.hpp"
#include <list>

class BlackHole : public ConcreteObject
{
public:
	BlackHole(double x, double y, Core::GameState &gameState);
	~BlackHole();

	virtual void	draw(double);
	void			createParticle(int angle);

private:
	Core::GameState &_gameState;
	double			_elapsedTime;
	int				_angle;
	std::list<ConcreteObject *>	_particles;
	int				_nbParticles;
};