#include "Ship.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"

Ship::Ship(std::string const &spriteName, std::string const &/*bulletFileName*/, float speed, int fireFrequency, int r, int g, int b, std::string const &group)
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency)
{
	if (this->_sprite)
		this->_sprite->setColor(r, g, b);
	if (!group.empty())
	  Core::GameStateManager::get().getCurrentState().addGameObject(this, group);
}

Ship::Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, std::pair<int, int> grabs[4], std::string const &group)
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency)

{
	if (this->_sprite)
		this->_sprite->setColor(r, g, b);

	Grab *grab;
	for (unsigned int i = 0; i < 4; ++i)
	  {
	    grab = new Grab("weapon", *(new Core::CircleHitBox(grabs[i].first, grabs[i].second, 5)), 0, 0);
	Core::GameStateManager::get().getCurrentState().addGameObject(grab, group);
	_grabs.push_back(grab);
	  }
}

Ship::~Ship()
{
  for (std::vector<Grab *>::iterator it = _grabs.begin();
       it != _grabs.end(); ++it)
    {
      delete *it;
    }
}
