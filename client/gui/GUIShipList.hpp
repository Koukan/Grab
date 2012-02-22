#pragma once

#include "GUIList.hpp"
#include "GUIButton.hpp"
#include "Player.hpp"
#include "Ship.hpp"
#include <vector>

class GUIShipList : public GUIList<GUIShipList>
{
public:
	GUIShipList(Player &player, unsigned int &nbReady, unsigned int nbPlayers, Core::ButtonSprite &leftArrow, Core::ButtonSprite &rightArrow,
		Core::ButtonSprite &middle, Core::GUILayout *layout, int r, int g, int b);
	~GUIShipList();

	virtual bool handleGUICommand(Core::GUICommand const &command);

	void changeShip(Core::GUIElement const &);
	void selectShip();

private:
	struct ShipInfo
	{
		ShipInfo(std::string const &shipname, std::string const &spritename, std::string const &bulletfilename, float speed, int firefrequency)
			: shipName(shipname), spriteName(spritename), bulletFileName(bulletfilename), speed(speed), fireFrequency(firefrequency)
		{
		}

		std::string const shipName;
		std::string const spriteName;
		std::string const bulletFileName;
		float speed;
		int fireFrequency;
	};

	Player					&_player;
	int						_currentShip;
	unsigned int			&_nbReady;
	unsigned int			_nbPlayers;
	std::vector<ShipInfo>	_shipInfos;
	int						_r;
	int						_g;
	int						_b;
	bool					_shipSelected;

	void addButtons(Core::ButtonSprite &middle);
};