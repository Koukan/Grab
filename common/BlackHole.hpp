#pragma once

#include "ConcreteObject.hpp"
#include "GameState.hpp"
#include <list>

class Ship;

class BlackHole : public ConcreteObject
{
public:
	BlackHole(double x, double y, Core::GameState &gameState, Ship &ship);
	~BlackHole();

	virtual void	draw(double);
	void			createParticle(int angle);
	bool			isEnd() const;

private:
	Core::GameState &_gameState;
	double			_elapsedTime;
	double			_elapsedTime2;
	int				_angle;
	std::list<ConcreteObject *>	_particles;
	unsigned int			_nbParticles;
	ConcreteObject	*_end;
	Ship			&_ship;
};
