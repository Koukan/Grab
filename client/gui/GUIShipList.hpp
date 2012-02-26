#pragma once

#include "GUIList.hpp"
#include "GUIShipButton.hpp"
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

	void changeShip(Core::GUIElement &);
	void selectShip();
	
	virtual void draw(double elapseTime);
	virtual void draw(int x, int y, double elapseTime);

private:
	GSShipSelection			&_shipSelection;
  Ship::ShipInfo					&_ship;
  Player const &_player;
	int						_currentShip;
	unsigned int			&_nbReady;
	unsigned int			_nbPlayers;
	bool					_shipSelected;
	GUIShipButton<GUIShipList> *_elem;
	int						_oldWidth;

	void addButtons(Core::ButtonSprite &middle);
};
