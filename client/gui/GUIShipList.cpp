#include "GUIShipList.hpp"
#include "GSShipSelection.hpp"

GUIShipList::GUIShipList(GSShipSelection &shipSelection, Player const &player, Ship::ShipInfo &ship, unsigned int &nbReady, unsigned int nbPlayers,
	Core::ButtonSprite &leftArrow, Core::ButtonSprite &rightArrow, Core::ButtonSprite &middle, Core::GUILayout *layout)
	: GUIList<GUIShipList>(*this, &GUIShipList::changeShip, leftArrow, rightArrow,
	layout, static_cast<Core::GUICommand::PlayerType>(player.getType())), _shipSelection(shipSelection),
	  _ship(ship), _player(player), _currentShip(0), _nbReady(nbReady), _nbPlayers(nbPlayers), _shipSelected(false), _elem(0),
	  _oldWidth(0)
{
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
		this->_width = this->_oldWidth;
		this->_shipSelected = false;
		--this->_nbReady;
		if (this->_elem)
			this->_elem->getSprite().updateState(Core::ButtonSprite::SELECTED);
		return (true);
	}
	return (false);
}

void GUIShipList::changeShip(Core::GUIElement &elem)
{
	GUIShipButton<GUIShipList> &shipButton = static_cast<GUIShipButton<GUIShipList> &>(elem);

	this->_elem = &shipButton;
	this->_currentShip = shipButton.getShipNb();
}

void GUIShipList::selectShip()
{
  _ship = Ship::shipsList[this->_currentShip];

	++this->_nbReady;
	this->_shipSelected = true;
	if (this->_elem)
	{
		this->_oldWidth = this->_width;
		this->_width = this->_elem->getWidth();
		this->_elem->getSprite().updateState(Core::ButtonSprite::CLICKED);
	}
	if (this->_nbReady == this->_nbPlayers)
	{
		this->_shipSelection.changeToInGame();
	}
}

void GUIShipList::addButtons(Core::ButtonSprite &middle)
{
  for (unsigned int i = 0; i < Ship::shipsListSize; ++i)
    {
      this->addElement(*(new GUIShipButton<GUIShipList>(i, *this, &GUIShipList::selectShip, Ship::shipsList[i].shipName, "buttonFont", middle, static_cast<Core::GUILayout *>(0), static_cast<Core::GUICommand::PlayerType>(this->_player.getType()))));
    }
}

void GUIShipList::draw(double elapseTime)
{
	if (this->_shipSelected && this->_elem)
		this->_elem->draw(elapseTime);
	else
		this->GUIList::draw(elapseTime);
}

void GUIShipList::draw(int x, int y, double elapseTime)
{
	if (this->_shipSelected && this->_elem)
		this->_elem->draw(x, y, elapseTime);
	else
		this->GUIList::draw(x, y, elapseTime);
}
