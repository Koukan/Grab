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
	enum BindState
	{
		NONE,
		SELECTED,
		BINDING
	};

	GUIPlayerButton(GSBindPlayer &bindPlayer, Core::Player *&player, int &nbPending, int &nbReady, Core::ButtonSprite const &sprite, std::string const &fontName, Core::GUILayout *layout);
	~GUIPlayerButton();

	virtual bool handleGUICommand(Core::GUICommand const &command);
	virtual void draw(double elapseTime);
	virtual void	draw(int x, int y, double elapseTime);

private:
	GSBindPlayer				&_bindPlayer;
	bool						_isSelect;
	bool						_isReady;
	BindState					_bindState;
	Core::Player				*&_player;
	int							&_nbPending;
	int							&_nbReady;
	Core::ButtonSprite			_sprite;
	Core::CoreFont				*_font;
	Core::CoreFont				*_bindFont;
	std::vector<std::string>	_bindActions;
	unsigned int				_bindIndex;

	void	changeToEmpty();
	void	changeToSelect(Core::GUICommand::PlayerType type);
	void	changeToReady(Core::GUICommand::PlayerType type);
};