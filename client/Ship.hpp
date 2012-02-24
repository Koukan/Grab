#pragma once

#include <vector>
#include "ConcreteObject.hpp"
#include "Sprite.hpp"
#include "Grab.hpp"

class Ship : public ConcreteObject
{
public:
  Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b);

  Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, std::pair<int, int> grabs[4]);

  ~Ship();

  void registerInGameObjectManager(std::string const &shipGroup,
				   std::string const &grabsGroup);
private:
	float			_speed;
	int				_fireFrequency;
  std::vector<Grab *> _grabs;

public:
	struct ShipInfo
	{
		std::string shipName;
		std::string spriteName;
		std::string bulletFileName;
		float speed;
		int fireFrequency;
	};
  static ShipInfo const	shipsList[];
  static unsigned int const shipsListSize;
};
