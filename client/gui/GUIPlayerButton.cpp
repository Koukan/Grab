#include "GUIPlayerButton.hpp"
#include "GameStateManager.hpp"
#include "GSBindPlayer.hpp"

GUIPlayerButton::GUIPlayerButton(GSBindPlayer &bindPlayer, Core::Player *&player, int &nbReady, Core::ButtonSprite const &sprite, std::string const &fontName, Core::GUILayout *layout)
	: Core::GUIElement(0, 0, sprite.getWidth(), sprite.getHeight(), layout, Core::GUICommand::ALL), _bindPlayer(bindPlayer), _isSelect(false),
	_player(player), _nbReady(nbReady), _sprite(sprite), _font(Core::GameStateManager::get().getCurrentState().getFont(fontName))
{
	if (this->_font)
		this->_font->setText("Empty");
}

GUIPlayerButton::~GUIPlayerButton()
{
}

bool GUIPlayerButton::handleGUICommand(Core::GUICommand const &command)
{
	if (command.type == Core::GUICommand::ACTION &&
		command.buttonAction == Core::GUICommand::PRESSED &&
		command.action == Core::GUICommand::SELECT)
	{
		if (!this->_isSelect)
		{
			if (this->_font)
			{
				if (command.playerType == Core::GUICommand::KEYBOARD)
					this->_font->setText("Keyboard : Start ?");
				else
					this->_font->setText("Joystick : Start ?");
			}
			this->_player = new Core::Player(static_cast<Core::Player::type>(command.playerType));
			++this->_nbReady;
			this->_isSelect = true;
			this->_playerType = command.playerType;
		}
		else
		{
			if (this->_font)
				this->_font->setText("Ready");
			--this->_nbReady;
			if (this->_nbReady == 0)
				this->_bindPlayer.goToShipSelection();
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
}

void	GUIPlayerButton::draw(int x, int y, double elapseTime)
{
	this->_sprite.draw(x, y, elapseTime);
	if (this->_font)
		this->_font->draw(static_cast<int>(x + (this->_sprite.getWidth() - this->_font->getWidth()) / 2),
		static_cast<int>(y + (this->_sprite.getHeight() - this->_font->getHeight()) / 2 - 5), elapseTime);
}
