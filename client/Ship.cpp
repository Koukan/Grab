#include "Ship.hpp"
#include "Grab.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"

Ship::ShipInfo const Ship::shipsList[] = {
  {"noname 1", "player1", "", 0.5, 400},
  {"noname 2", "player2", "", 0.5, 800},
  {"noname 3", "player3", "", 0.5, 200}
};

unsigned int const Ship::shipsListSize = sizeof(Ship::shipsList) / sizeof(*Ship::shipsList);

Ship::Ship(std::string const &spriteName, std::string const &/*bulletFileName*/, float speed, int fireFrequency, int r, int g, int b, unsigned int nbMaxGrabs)
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency), _nbMaxGrabs(nbMaxGrabs), _grabLaunched(false)
{
	if (this->_sprite)
		this->_sprite->setColor(r, g, b);
}

Ship::Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, std::pair<int, int> grabs[4], unsigned int nbMaxGrabs)
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency), _nbMaxGrabs(nbMaxGrabs), _grabLaunched(false)
{
	if (this->_sprite)
		this->_sprite->setColor(r, g, b);

	Grab *grab;
	for (unsigned int i = 0; i < nbMaxGrabs; ++i)
	  {
	    grab = new Grab("weapon", *(new Core::CircleHitBox(grabs[i].first, grabs[i].second, 5)), 0, 0, *this);
	_grabs.push_back(grab);
	  }
}

Ship::~Ship()
{
}

void Ship::registerInGameObjectManager(std::string const &shipGroup,
				       std::string const &grabsGroup)
{
  Core::GameStateManager::get().getCurrentState().addGameObject(this, shipGroup);
  for (std::vector<Grab *>::iterator it = _grabs.begin();
       it != _grabs.end(); ++it)
    {
      Core::GameStateManager::get().getCurrentState().addGameObject(*it, grabsGroup);
    }
}

#include <iostream>
void Ship::launchGrab(std::string const &group)
{
  std::cout << "launchGrab" << std::endl;;
  if (/*!_grabLaunched &&*/ _grabs.size() < _nbMaxGrabs)
    {
      std::cout << " " << "true" << std::endl;
      Grab* grab = new Grab("bullet", *(new Core::RectHitBox(this->getX(), this->getY(), 100, 100)), 0, -100, *this);
      Core::GameStateManager::get().getCurrentState().addGameObject(grab, group);
      _grabLaunched = true;
    }
}

void Ship::setGrabLaunched(bool grabLaunched)
{
  _grabLaunched = grabLaunched;
}

bool Ship::getGrabLaunched() const
{
  return (_grabLaunched);
}

void Ship::addGrab(Grab *grab)
{
  if (grab)
    _grabs.push_back(grab);
}
