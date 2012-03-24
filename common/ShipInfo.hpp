#pragma once

#include <string>
#include "Ship.hpp"

namespace	ShipInfo
{
	struct	ShipInfo
	{
		std::string				shipName;
		std::string				spriteName;
		std::string				bulletFileName;
		float					speed;
		int						fireFrequency;
		GrabPosition::Position	grab1;
		GrabPosition::Position	grab2;
		GrabPosition::Position	grab3;
		void (Ship::*specialPower)();
	};

	static ShipInfo const		shipsList[] = {
  {"Conqueror", "player1", "player3", 450, 400,
   GrabPosition::MIDDLE_TOP, GrabPosition::LEFT_BOTTOM_CORNER, GrabPosition::RIGHT_BOTTOM_CORNER, &Ship::bomb},
  {"Voyageer", "player2", "player3", 450, 800,
   GrabPosition::MIDDLE_BOTTOM, GrabPosition::LEFT_TOP_CORNER, GrabPosition::RIGHT_TOP_CORNER, &Ship::shield},
  {"Obliterator", "player3", "player3", 450, 200,
   GrabPosition::MIDDLE_BOTTOM, GrabPosition::LEFT_BOTTOM_CORNER, GrabPosition::RIGHT_BOTTOM_CORNER, 0},
  {"Replicator", "player4", "player3", 450, 200,
   GrabPosition::MIDDLE_TOP, GrabPosition::LEFT_BOTTOM_CORNER, GrabPosition::RIGHT_BOTTOM_CORNER, 0},
  {"LadyBird", "player5", "player3", 450, 200,
   GrabPosition::MIDDLE_TOP, GrabPosition::LEFT, GrabPosition::RIGHT, 0},
	};
	static unsigned int const	shipsListSize = sizeof(shipsList) / sizeof(*shipsList);
};
