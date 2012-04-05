#pragma once

#include <string>
#include "Grab.hpp"

namespace	ShipInfo
{
	enum	SpecialPower
	  {
	    NONE = 0,
	    SHIELD,
	    BOMB
	  };

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
		SpecialPower				specialPowerType;
	};

	static ShipInfo const		shipsList[] = {
  {"Replicator", "player4", "player4", "concentratedPlayer4", 500, 200,
   GrabPosition::MIDDLE_TOP, 0, GrabPosition::LEFT_BOTTOM_CORNER, 0, GrabPosition::RIGHT_BOTTOM_CORNER, 0, SHIELD},
  {"Obliterator", "player3", "player2", "concentratedPlayer2", 500, 200,
   GrabPosition::MIDDLE_BOTTOM, 180, GrabPosition::LEFT_BOTTOM_CORNER, 90, GrabPosition::RIGHT_BOTTOM_CORNER, -90, NONE},
  {"Conqueror", "player1", "player3", "concentratedPlayer3", 500, 400,
   GrabPosition::MIDDLE_TOP, 0, GrabPosition::LEFT_BOTTOM_CORNER, 0, GrabPosition::RIGHT_BOTTOM_CORNER, 0, BOMB},
  {"Voyageer", "player2", "player3", "concentratedPlayer3", 500, 800,
   GrabPosition::MIDDLE_BOTTOM, 0, GrabPosition::LEFT_TOP_CORNER, 0, GrabPosition::RIGHT_TOP_CORNER, 0, SHIELD},
  {"LadyBird", "player5", "player3", "concentratedPlayer3", 500, 200,
   GrabPosition::MIDDLE_TOP, 0, GrabPosition::LEFT, 0, GrabPosition::RIGHT, 0, NONE},
	};
	static unsigned int const	shipsListSize = sizeof(shipsList) / sizeof(*shipsList);
};
