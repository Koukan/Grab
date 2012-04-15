#include "GUIPlayerButton.hpp"
#include "GameStateManager.hpp"
#include "GSBindPlayer.hpp"
#include "Ship.hpp"
#include "GameCommand.hpp"
#include "CommandDispatcher.hpp"
#include "ShipInfo.hpp"

GUIPlayerButton::GUIPlayerButton(GSBindPlayer &bindPlayer, Player *&player, int &nbPending, int &nbReady, Core::ButtonSprite const &sprite, std::string const &fontName, Core::GUILayout *layout, uint32_t nb)
	: Core::GUIElement(0, 0, sprite.getWidth(), sprite.getHeight(), layout, Core::GUICommand::ALL), _bindPlayer(bindPlayer), _isSelect(false),
	_isReady(false), _bindState(GUIPlayerButton::NONE), _player(player), _nbPending(nbPending), _nbReady(nbReady), _ship(0), _sprite(sprite),
	_font(Core::GameStateManager::get().getCurrentState().getFont(fontName)),
	_bindFont(Core::GameStateManager::get().getCurrentState().getFont(fontName)),
	_shipFont(Core::GameStateManager::get().getCurrentState().getFont(fontName)), _bindIndex(0), _nb(nb)
{
	this->changeToEmpty();
	if (this->_bindFont)
	{
		this->_bindFont->setTransparency(100);
		this->_bindFont->setText("bind");
	}
	if (this->_shipFont)
		this->_shipFont->setText(ShipInfo::shipsList[this->_ship].shipName);

	this->_bindActions.push_back("Fire");
	this->_bindActions.push_back("Special Fire");
	this->_bindActions.push_back("Pause");
}

GUIPlayerButton::~GUIPlayerButton()
{
	if (this->_font)
	    delete this->_font;
	if (this->_bindFont)
	    delete this->_bindFont;
}

bool	GUIPlayerButton::handleGUICommand(Core::GUICommand const &command)
{
	if (this->_bindState != GUIPlayerButton::BINDING)
	{
		if (this->_isSelect && command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::PRESSED)
			return this->directionCommand(command);
		else if (command.type == Core::GUICommand::ACTION && command.buttonAction == Core::GUICommand::RELEASED)
		{
			if (command.action == Core::GUICommand::SELECT)
				return this->selectCommand(command);
			else if (this->_isSelect && command.action == Core::GUICommand::BACK)
				return this->backCommand(command);
		}
	}
	else if (command.type != Core::GUICommand::DIRECTION &&
			command.buttonAction == Core::GUICommand::RELEASED)
		return bindState(command);
	return (false);
}

bool	GUIPlayerButton::selectCommand(Core::GUICommand const &command)
{
	if (this->_isReady)
		return (true);
	GUIPlayerButton	*button = this->_bindPlayer.selectedBy(command.playerType);
	if (button != 0 && button != this)
		return (false);
	if (!this->_isSelect)
	{

		if (this->_bindPlayer.isOnline())
			this->_bindPlayer.addDemand(command.playerType);
		else
		{
			this->_bindPlayer.addSelected(this, command.playerType);
			this->_playerType = command.playerType;
			this->_player = new Player(static_cast<Player::type>(command.playerType));
			this->changeToSelect();
		}
	}
	else
	{
		if (this->_bindState == GUIPlayerButton::NONE)
		{
			this->changeToReady();
			this->_bindPlayer.updatePlayer(_nb, _ship, _isReady);
		}
		else
		{
			this->_bindState = GUIPlayerButton::BINDING;
			if (this->_bindFont)
				this->_bindFont->setText("bind \"" + this->_bindActions[this->_bindIndex] + "\"");
		}
	}
	return (true);
}

bool	GUIPlayerButton::backCommand(Core::GUICommand const &command)
{
	if (this->_isReady)
	{
		this->changeToSelect();
		this->_bindPlayer.updatePlayer(_nb, _ship, _isReady);
	}
	else
	{
		this->changeToEmpty();
		this->_bindPlayer.removeSelected(command.playerType);
	}
	return (true);
}

bool	GUIPlayerButton::directionCommand(Core::GUICommand const &command)
{
	if (this->_isReady)
		return (true);
	if (command.direction == Core::GUICommand::LEFT || command.direction == Core::GUICommand::RIGHT)
	{
		if (this->_bindState == GUIPlayerButton::NONE)
		{
			this->_bindState = GUIPlayerButton::SELECTED;
			if (this->_bindFont)
				this->_bindFont->setTransparency(255);
		}
		else if (this->_bindState == GUIPlayerButton::SELECTED)
		{
			this->_bindState = GUIPlayerButton::NONE;
			if (this->_bindFont)
				this->_bindFont->setTransparency(100);
		}
		return (true);
	}
	else if (command.direction == Core::GUICommand::UP)
	{
		if (this->_ship == 0)
			this->_ship = ShipInfo::shipsListSize - 1;
		else
			this->_ship--;
		this->changeShip();
		this->_bindPlayer.updatePlayer(_nb, _ship, _isReady);
		return (true);
	}
	else if (command.direction == Core::GUICommand::DOWN)
	{
		if (this->_ship == ShipInfo::shipsListSize - 1)
			this->_ship = 0;
		else
			this->_ship++;
		this->changeShip();
		this->_bindPlayer.updatePlayer(_nb, _ship, _isReady);
		return (true);
	}
	return false;
}

bool	GUIPlayerButton::bindState(Core::GUICommand const &command)
{
	Core::InputCommand &cmd = this->_player->getAction(static_cast<Player::Action>(this->_bindIndex));
	if (command.playerType == Core::GUICommand::KEYBOARD)
	{
		cmd.Type = Core::InputCommand::KeyReleased;
		cmd.Key.Code = static_cast<Core::Keyboard::Key>(command.id);
	}
	else
	{
		cmd.Type = Core::InputCommand::JoystickButtonReleased;
		cmd.JoystickButton.JoystickId = static_cast<unsigned int>(command.playerType - 1);
		cmd.JoystickButton.Button = command.id;
	}
	if (this->_bindIndex + 1 < this->_bindActions.size())
	{
		++this->_bindIndex;
		if (this->_bindFont)
			this->_bindFont->setText("bind \"" + this->_bindActions[this->_bindIndex] + "\"");
	}
	else
	{
		this->_bindIndex = 0;
		this->_bindState = GUIPlayerButton::NONE;
		if (this->_bindFont)
		{
			this->_bindFont->setColor(255, 255, 255);
			this->_bindFont->setText("bind");
		}
	}
	return (true);
}

void	GUIPlayerButton::draw(double elapseTime)
{
	this->_sprite.draw(0, 0, elapseTime);
	if (this->_font)
		this->_font->draw(static_cast<int>(0 + (this->_sprite.getWidth() - this->_font->getWidth()) / 2) - 7,
		static_cast<int>(35), elapseTime);
	if (!this->_isReady && this->_isSelect && this->_bindFont && !this->_bindPlayer.isOnline())
		this->_bindFont->draw(static_cast<int>(this->_sprite.getWidth() - 160),
		static_cast<int>(35), elapseTime);
	if (this->_isSelect && this->_shipFont)
		this->_shipFont->draw(-50,
		static_cast<int>(35), elapseTime);
}

void	GUIPlayerButton::draw(int x, int y, double elapseTime)
{
	this->_sprite.draw(x, y, elapseTime);
	if (this->_font)
		this->_font->draw(static_cast<int>(x + (this->_sprite.getWidth() - this->_font->getWidth()) / 2) - 7,
		static_cast<int>(y + 35), elapseTime);
	if (!this->_isReady && this->_isSelect && this->_bindFont && !this->_bindPlayer.isOnline())
		this->_bindFont->draw(static_cast<int>(x + this->_sprite.getWidth() - 160),
		static_cast<int>(y + 35), elapseTime);
	if (this->_isSelect && this->_shipFont)
		this->_shipFont->draw(x - 50,
		static_cast<int>(y + 35), elapseTime);
}

void	GUIPlayerButton::addPlayer(Core::GUICommand::PlayerType type)
{
	this->_playerType = type;
	this->_player = new Player(static_cast<Player::type>(type));
	this->changeToSelect();
}

void	GUIPlayerButton::updatePlayer(uint32_t ship, bool ready)
{
	if (this->_playerType == Core::GUICommand::ALL);
		this->_playerType = Core::GUICommand::ONLINE;
	this->_ship = ship;
	if (!this->_player)
	{
		this->_player = new Player(static_cast<Player::type>(Core::GUICommand::ONLINE));
		this->changeToSelect();
	}
	if (this->_isReady && !ready)
	{
		--this->_nbReady;
		this->_isReady = false;
		this->changeToSelect();
	}
	else if (!this->_isReady && ready)
		this->changeToReady();
	this->changeShip();
}

void	GUIPlayerButton::changeToEmpty()
{
	this->_playerType = Core::GUICommand::ALL;
	this->_sprite.updateState(Core::ButtonSprite::DEFAULT);
	if (this->_font)
		this->_font->setText("Empty");
	this->_isSelect = false;
	if (this->_player)
	{
		--this->_nbPending;
		if (this->_nbPending == 0 && this->_nbReady > 0 && !this->_bindPlayer.isOnline())
			this->_bindPlayer.goToInGame();
		delete this->_player;
		this->_player = 0;
		this->_bindPlayer.removePlayer(this->_nb, this->_playerType);
	}
}

void	GUIPlayerButton::changeToSelect()
{
	this->_sprite.updateState(Core::ButtonSprite::SELECTED);
	if (this->_font)
	{
		if (this->_playerType == Core::GUICommand::ONLINE)
			this->_font->setText("Online : Start ?");
		else if (this->_playerType == Core::GUICommand::KEYBOARD)
			this->_font->setText("Keyboard : Start ?");
		else
			this->_font->setText("Joystick : Start ?");
	}
	this->_player->setShipInfo(&ShipInfo::shipsList[this->_ship]);
	++this->_nbPending;
	this->_isSelect = true;
	if (this->_isReady)
	{
		--this->_nbReady;
		this->_isReady = false;
	}
}

void	GUIPlayerButton::changeToReady()
{
	if (this->_font)
	{
		if (this->_playerType == Core::GUICommand::ONLINE)
			this->_font->setText("Online : Ready");
		else if (this->_playerType == Core::GUICommand::KEYBOARD)
			this->_font->setText("Keyboard : Ready");
		else
			this->_font->setText("Joystick : Ready");
	}
	--this->_nbPending;
	++this->_nbReady;
	if (this->_nbPending == 0 && !this->_bindPlayer.isOnline())
		this->_bindPlayer.goToInGame();
	this->_isReady = true;
}

void	GUIPlayerButton::changeShip()
{
	this->_shipFont->setText(ShipInfo::shipsList[this->_ship].shipName);
	this->_player->setShipInfo(&ShipInfo::shipsList[this->_ship]);
}
