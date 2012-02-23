#include "Ship.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"

Ship::ShipInfo const Ship::shipsList[] = {
  {"noname 1", "player1", "", 0.5, 400},
  {"noname 2", "player2", "", 0.5, 800},
  {"noname 3", "player3", "", 0.5, 200}
};

unsigned int const Ship::shipsListSize = sizeof(Ship::shipsList) / sizeof(*Ship::shipsList);

Ship::Ship(std::string const &spriteName, std::string const &/*bulletFileName*/, float speed, int fireFrequency, int r, int g, int b)
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency)
{
	if (this->_sprite)
		this->_sprite->setColor(r, g, b);
}

Ship::Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, std::pair<int, int> grabs[4])
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency)

{
	if (this->_sprite)
		this->_sprite->setColor(r, g, b);

	Grab *grab;
	for (unsigned int i = 0; i < 4; ++i)
	  {
	    grab = new Grab("weapon", *(new Core::CircleHitBox(grabs[i].first, grabs[i].second, 5)), 0, 0);
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


