#pragma once

#include <string>

namespace	GrabPosition
{
  //    8     16     32
  // 1  LTC   MT      LBC
  //
  // 2  L     M       R
  //
  // 4  LBC   MB      RBC
	enum Position
    {
		LEFT_TOP_CORNER = 9,
		MIDDLE_TOP = 17,
		RIGHT_TOP_CORNER = 33,
		LEFT = 10,
		MIDDLE = 18,
		RIGHT = 34,
		LEFT_BOTTOM_CORNER = 12,
		MIDDLE_BOTTOM = 20,
		RIGHT_BOTTOM_CORNER = 36
    };
};

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
	};

	static ShipInfo const		shipsList[] = {
  {"Conqueror", "player1", "player3", 450, 400,
   GrabPosition::MIDDLE_TOP, GrabPosition::LEFT_BOTTOM_CORNER, GrabPosition::RIGHT_BOTTOM_CORNER},
  {"Voyageer", "player2", "player3", 450, 800,
   GrabPosition::MIDDLE_BOTTOM, GrabPosition::LEFT_TOP_CORNER, GrabPosition::RIGHT_TOP_CORNER},
  {"Obliterator", "player3", "player3", 450, 200,
   GrabPosition::MIDDLE_TOP, GrabPosition::LEFT_BOTTOM_CORNER, GrabPosition::RIGHT_BOTTOM_CORNER}
	};
	static unsigned int const	shipsListSize = sizeof(shipsList) / sizeof(*shipsList);
};
