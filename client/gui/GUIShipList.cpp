#include "GUIShipList.hpp"
#include "GUIShipButton.hpp"
#include "GSShipSelection.hpp"

GUIShipList::GUIShipList(GSShipSelection &shipSelection, Player &player, unsigned int &nbReady, unsigned int nbPlayers,
	Core::ButtonSprite &leftArrow, Core::ButtonSprite &rightArrow, Core::ButtonSprite &middle, Core::GUILayout *layout, int r, int g, int b)
	: GUIList<GUIShipList>(*this, &GUIShipList::changeShip, leftArrow, rightArrow,
	layout, static_cast<Core::GUICommand::PlayerType>(player.getType())), _shipSelection(shipSelection),
	_player(player), _currentShip(0), _nbReady(nbReady), _nbPlayers(nbPlayers), _r(r), _g(g), _b(b), _shipSelected(false)
{
  	this->_shipInfos.push_back(ShipInfo("noname 1", "player1", "", 0.5, 400));
	this->_shipInfos.push_back(ShipInfo("noname 2", "player2", "", 0.5, 800));
	this->_shipInfos.push_back(ShipInfo("noname 3", "player3", "", 0.5, 200));
	this->addButtons(middle);
}

GUIShipList::~GUIShipList()
{
}

bool GUIShipList::handleGUICommand(Core::GUICommand const &command)
{
	if (!this->_shipSelected)
		return (this->GUIList::handleGUICommand(command));
	if (command.type == Core::GUICommand::ACTION &&
		command.buttonAction == Core::GUICommand::RELEASED &&
		command.action == Core::GUICommand::BACK)
	{
		this->_shipSelected = false;
		--this->_nbReady;
		delete this->_player.getShip();
		return (true);
	}
	return (false);
}

void GUIShipList::changeShip(Core::GUIElement const &elem)
{
	GUIShipButton<GUIShipList> const &shipButton = static_cast<GUIShipButton<GUIShipList> const &>(elem);

	this->_currentShip = shipButton.getShipNb();
}

void GUIShipList::selectShip()
{
	ShipInfo &shipInfo = this->_shipInfos[this->_currentShip];
	this->_player.setShip(new Ship(shipInfo.spriteName, shipInfo.bulletFileName, shipInfo.speed,
			shipInfo.fireFrequency, this->_r, this->_g, this->_b));
	++this->_nbReady;
	this->_shipSelected = true;
	if (this->_nbReady == this->_nbPlayers)
	{
		this->_shipSelection.changeToInGame();
	}
}

void GUIShipList::addButtons(Core::ButtonSprite &middle)
{
	for (unsigned int i = 0; i < this->_shipInfos.size(); ++i)
	{
		this->addElement(*(new GUIShipButton<GUIShipList>(i, *this, &GUIShipList::selectShip, this->_shipInfos[i].shipName,
			"buttonFont", middle, static_cast<Core::GUILayout *>(0), static_cast<Core::GUICommand::PlayerType>(this->_player.getType()))));
	}
}
