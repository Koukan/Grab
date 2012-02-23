#pragma once

#include <vector>
#include "ConcreteObject.hpp"
#include "Sprite.hpp"
#include "Grab.hpp"

class Ship : public ConcreteObject
{
public:
  Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, std::string const &group = "");

  Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, std::pair<int, int> grabs[4], std::string const &group);

  ~Ship();

private:
	float			_speed;
	int				_fireFrequency;
  std::vector<Grab *> _grabs;
};
