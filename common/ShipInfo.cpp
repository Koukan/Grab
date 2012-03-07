#include "ShipInfo.hpp"


Ship::ShipInfo const Ship::shipsList[] = {
  {"Conqueror", "player1", "player3", 300, 400,
   Grab::MIDDLE_TOP, Grab::LEFT_BOTTOM_CORNER, Grab::RIGHT_BOTTOM_CORNER},
  {"Voyageer", "player2", "player3", 300, 800,
   Grab::MIDDLE_BOTTOM, Grab::LEFT_TOP_CORNER, Grab::RIGHT_TOP_CORNER},
  {"Obliterator", "player3", "player3", 300, 200,
   Grab::MIDDLE_TOP, Grab::LEFT_BOTTOM_CORNER, Grab::RIGHT_BOTTOM_CORNER}
};
