#pragma once

#include "GUIElement.hpp"
#include "Player.hpp"
#include "ButtonSprite.hpp"
#include "Font.hpp"
#include "GUILayout.hpp"
#include <list>

class GSBindPlayer;

class GUIPlayerButton : public Core::GUIElement
{
public:
	GUIPlayerButton(GSBindPlayer &bindPlayer, Core::Player *&player, int &nbReady, Core::ButtonSprite const &sprite, std::string const &fontName, Core::GUILayout *layout);
	~GUIPlayerButton();

	virtual bool handleGUICommand(Core::GUICommand const &command);
	virtual void draw(double elapseTime);
	virtual void	draw(int x, int y, double elapseTime);

private:
	GSBindPlayer		&_bindPlayer;
	bool				_isSelect;
	Core::Player		*&_player;
	int					&_nbReady;
	Core::ButtonSprite	_sprite;
	Core::CoreFont		*_font;
};