#pragma once

#include "GUIList.hpp"
#include "GUIButton.hpp"
#include "Player.hpp"
#include "Ship.hpp"
#include <vector>

class GSShipSelection;

class GUIShipList : public GUIList<GUIShipList>
{
public:
  GUIShipList(GSShipSelection &shipSelection, Player const &player, Ship::ShipInfo &_selectedShip, unsigned int &nbReady, unsigned int nbPlayers, Core::ButtonSprite &leftArrow, Core::ButtonSprite &rightArrow, Core::ButtonSprite &middle, Core::GUILayout *layout);
	~GUIShipList();

	virtual bool handleGUICommand(Core::GUICommand const &command);

	void changeShip(Core::GUIElement const &);
	void selectShip();

public:
	GSShipSelection			&_shipSelection;
  Ship::ShipInfo					&_ship;
  Player const &_player;
	int						_currentShip;
	unsigned int			&_nbReady;
	unsigned int			_nbPlayers;
	bool					_shipSelected;

	void addButtons(Core::ButtonSprite &middle);
};
