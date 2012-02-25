#include "GUIPlayerButton.hpp"
#include "GameStateManager.hpp"
#include "GSBindPlayer.hpp"

GUIPlayerButton::GUIPlayerButton(GSBindPlayer &bindPlayer, Player *&player, int &nbPending, int &nbReady, Core::ButtonSprite const &sprite, std::string const &fontName, Core::GUILayout *layout)
	: Core::GUIElement(0, 0, sprite.getWidth(), sprite.getHeight(), layout, Core::GUICommand::ALL), _bindPlayer(bindPlayer), _isSelect(false),
	_isReady(false), _bindState(GUIPlayerButton::NONE), _player(player), _nbPending(nbPending), _nbReady(nbReady), _sprite(sprite),
	_font(Core::GameStateManager::get().getCurrentState().getFont(fontName)),
	_bindFont(Core::GameStateManager::get().getCurrentState().getFont(fontName)), _bindIndex(0)
{
	this->changeToEmpty();
	if (this->_bindFont)
	{
/*		this->_bindFont->setColor(0, 100, 255);*/
		this->_bindFont->setText("bind");
	}

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

bool GUIPlayerButton::handleGUICommand(Core::GUICommand const &command)
{
	if (this->_bindState != GUIPlayerButton::BINDING)
	{
		if (this->_isSelect && command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::PRESSED &&
			(command.direction == Core::GUICommand::LEFT || command.direction == Core::GUICommand::RIGHT))
		{
			if (this->_bindState == GUIPlayerButton::NONE)
			{
				this->_bindState = GUIPlayerButton::SELECTED;
				if (this->_bindFont)
					this->_bindFont->setColor(0, 100, 255);
			}
			else if (this->_bindState == GUIPlayerButton::SELECTED)
			{
				this->_bindState = GUIPlayerButton::NONE;
				if (this->_bindFont)
					this->_bindFont->setColor(255, 255, 255);
			}
			return (true);
		}
		else if (command.type == Core::GUICommand::ACTION &&
			command.buttonAction == Core::GUICommand::RELEASED)
		{
			if (command.action == Core::GUICommand::SELECT)
			{
				if (!this->_isSelect)
				{
					this->changeToSelect(command.playerType);
					this->_player = new Player(static_cast<Player::type>(command.playerType));
					++this->_nbPending;
					this->_isSelect = true;
					this->_playerType = command.playerType;
				}
				else
				{
					if (this->_bindState == GUIPlayerButton::NONE)
						this->changeToReady(this->_playerType);
					else
					{
						this->_bindState = GUIPlayerButton::BINDING;
						if (this->_bindFont)
							this->_bindFont->setText("bind \"" + this->_bindActions[this->_bindIndex] + "\"");
					}
				}
				return (true);
			}
			else if (this->_isSelect && command.action == Core::GUICommand::BACK)
			{
				if (this->_isReady)
				{
					--this->_nbReady;
					this->changeToSelect(this->_playerType);
					this->_isReady = false;
					++this->_nbPending;
				}
				else
				{
					delete this->_player;
					this->_player = 0;
					--this->_nbPending;
					if (this->_nbPending == 0 && this->_nbReady > 0)
						this->_bindPlayer.goToShipSelection();
					this->changeToEmpty();
					this->_playerType = Core::GUICommand::ALL;
					this->_isSelect = false;
				}
				return (true);
			}
		}
	}
	else if (command.type != Core::GUICommand::DIRECTION &&
			command.buttonAction == Core::GUICommand::RELEASED)
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
	return (false);
}

void GUIPlayerButton::draw(double elapseTime)
{
	this->_sprite.draw(0, 0, elapseTime);
	if (this->_font)
		this->_font->draw(static_cast<int>(0 + (this->_sprite.getWidth() - this->_font->getWidth()) / 2),
		static_cast<int>(0 + (this->_sprite.getHeight() - this->_font->getHeight()) / 2 - 5), elapseTime);
	if (this->_isSelect && this->_bindFont)
		this->_bindFont->draw(static_cast<int>(0 + this->_sprite.getWidth() + 40),
		static_cast<int>(0 + (this->_sprite.getHeight() - this->_bindFont->getHeight()) / 2 - 5), elapseTime);
}

void	GUIPlayerButton::draw(int x, int y, double elapseTime)
{
	this->_sprite.draw(x, y, elapseTime);
	if (this->_font)
		this->_font->draw(static_cast<int>(x + (this->_sprite.getWidth() - this->_font->getWidth()) / 2),
		static_cast<int>(y + (this->_sprite.getHeight() - this->_font->getHeight()) / 2 - 5), elapseTime);
	if (this->_isSelect && this->_bindFont)
		this->_bindFont->draw(static_cast<int>(x + this->_sprite.getWidth() + 40),
		static_cast<int>(y + (this->_sprite.getHeight() - this->_bindFont->getHeight()) / 2 - 5), elapseTime);
}

void	GUIPlayerButton::changeToEmpty()
{
	if (this->_font)
		this->_font->setText("Empty");
}

void	GUIPlayerButton::changeToSelect(Core::GUICommand::PlayerType type)
{
	if (this->_font)
	{
		if (type == Core::GUICommand::KEYBOARD)
			this->_font->setText("Keyboard : Start ?");
		else
			this->_font->setText("Joystick : Start ?");
	}
}

void	GUIPlayerButton::changeToReady(Core::GUICommand::PlayerType type)
{
	if (this->_font)
	{
		if (type == Core::GUICommand::KEYBOARD)
			this->_font->setText("Keyboard : Ready");
		else
			this->_font->setText("Joystick : Ready");
	}
	--this->_nbPending;
	++this->_nbReady;
	if (this->_nbPending == 0)
		this->_bindPlayer.goToShipSelection();
	this->_isReady = true;
}
