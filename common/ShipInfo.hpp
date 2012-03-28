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
		std::string				concentratedBulletFileName;
		float					speed;
		int						fireFrequency;
		GrabPosition::Position	grab1;
		GrabPosition::Position	grab2;
		GrabPosition::Position	grab3;
		void (Ship::*specialPower)();
	};

	static ShipInfo const		shipsList[] = {
  {"Replicator", "player4", "player4", "concentratedPlayer4", 600, 200,
   GrabPosition::MIDDLE_TOP, GrabPosition::LEFT_BOTTOM_CORNER, GrabPosition::RIGHT_BOTTOM_CORNER, 0},
  {"Obliterator", "player3", "player2", "concentratedPlayer2", 600, 200,
   GrabPosition::MIDDLE_BOTTOM, GrabPosition::LEFT_BOTTOM_CORNER, GrabPosition::RIGHT_BOTTOM_CORNER, 0},
  {"Conqueror", "player1", "player3", "concentratedPlayer3", 600, 400,
   GrabPosition::MIDDLE_TOP, GrabPosition::LEFT_BOTTOM_CORNER, GrabPosition::RIGHT_BOTTOM_CORNER, &Ship::bomb},
  {"Voyageer", "player2", "player3", "concentratedPlayer3", 600, 800,
   GrabPosition::MIDDLE_BOTTOM, GrabPosition::LEFT_TOP_CORNER, GrabPosition::RIGHT_TOP_CORNER, &Ship::shield},
  {"LadyBird", "player5", "player3", "concentratedPlayer3", 600, 200,
   GrabPosition::MIDDLE_TOP, GrabPosition::LEFT, GrabPosition::RIGHT, 0},
	};
	static unsigned int const	shipsListSize = sizeof(shipsList) / sizeof(*shipsList);
};
