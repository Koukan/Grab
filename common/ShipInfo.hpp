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
		int						grabAngle1;
		GrabPosition::Position	grab2;
		int						grabAngle2;
		GrabPosition::Position	grab3;
		int						grabAngle3;
		void (Ship::*specialPower)();
	};

	static ShipInfo const		shipsList[] = {
  {"Replicator", "player4", "player4", "concentratedPlayer4", 500, 200,
   GrabPosition::MIDDLE_TOP, 0, GrabPosition::LEFT_BOTTOM_CORNER, 0, GrabPosition::RIGHT_BOTTOM_CORNER, 0, 0},
  {"Obliterator", "player3", "player2", "concentratedPlayer2", 500, 200,
   GrabPosition::MIDDLE_BOTTOM, 180, GrabPosition::LEFT_BOTTOM_CORNER, 90, GrabPosition::RIGHT_BOTTOM_CORNER, -90, 0},
  {"Conqueror", "player1", "player3", "concentratedPlayer3", 500, 400,
   GrabPosition::MIDDLE_TOP, 0, GrabPosition::LEFT_BOTTOM_CORNER, 0, GrabPosition::RIGHT_BOTTOM_CORNER, 0, &Ship::bomb},
  {"Voyageer", "player2", "player3", "concentratedPlayer3", 500, 800,
   GrabPosition::MIDDLE_BOTTOM, 0, GrabPosition::LEFT_TOP_CORNER, 0, GrabPosition::RIGHT_TOP_CORNER, 0, &Ship::shield},
  {"LadyBird", "player5", "player3", "concentratedPlayer3", 500, 200,
   GrabPosition::MIDDLE_TOP, 0, GrabPosition::LEFT, 0, GrabPosition::RIGHT, 0, 0},
	};
	static unsigned int const	shipsListSize = sizeof(shipsList) / sizeof(*shipsList);
};
