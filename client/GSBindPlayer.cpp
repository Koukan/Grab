#include "GSBindPlayer.hpp"
#include "GSShipSelection.hpp"
#include "GUIPlayerButton.hpp"
#include "GUIVLayout.hpp"
#include "GameStateManager.hpp"
#include "RendererManager.hpp"

GSBindPlayer::GSBindPlayer(Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online)
  : Core::GameState("bindPlayers", true), _mode(mode), _map(map), _nbPlayers(nbPlayers), _online(online), _nbReady(0), _nbPending(0)
{
	this->_players[0] = 0;
	this->_players[1] = 0;
	this->_players[2] = 0;
	this->_players[3] = 0;
}

GSBindPlayer::~GSBindPlayer()
{
}

void GSBindPlayer::onStart()
{
	// load xml
	this->load("resources/intro.xml");

	// add gui

	Core::GUILayout *layout = new GUIVLayout(RendererManager::get().getWidth() / 2,
		(RendererManager::get().getHeight() - 100) / 2, 300, 300, 20, 100, "up arrow", "down arrow");
	layout->setY((RendererManager::get().getHeight() - layout->getHeight()) / 2);
	layout->setDispatch(true);

	Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");

	for (unsigned int i = 0; i < this->_nbPlayers; ++i)
		new GUIPlayerButton(*this, *(this->_players + i), this->_nbPending, this->_nbReady, *sprite, "buttonFont", layout);
}

void GSBindPlayer::goToShipSelection()
{
	std::list<Player *> *players = new std::list<Player *>();

	for (int i = 0; i < 4; ++i)
	{
		if (this->_players[i])
			players->push_back(this->_players[i]);
	}
	Core::GameState *shipSelection = new GSShipSelection(players, this->_mode, this->_map, this->_nbPlayers, _online);
	Core::GameStateManager::get().pushState(*shipSelection);
}
