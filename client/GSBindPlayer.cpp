#include "GSBindPlayer.hpp"
#include "GSInGame.hpp"
#include "GUIPlayerButton.hpp"
#include "GUIVLayout.hpp"
#include "GameStateManager.hpp"
#include "RendererManager.hpp"

GSBindPlayer::GSBindPlayer(Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online)
  : Core::GameState("bindPlayers", true), _mode(mode), _map(map), _nbPlayers(nbPlayers), _online(online), _nbReady(0), _nbPending(0), _id(0)
{
	this->_players[0] = 0;
	this->_players[1] = 0;
	this->_players[2] = 0;
	this->_players[3] = 0;
}

GSBindPlayer::~GSBindPlayer()
{
}

void	GSBindPlayer::onStart()
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

void	GSBindPlayer::goToInGame()
{
	std::list<Player *> *players = new std::list<Player *>();

	for (int i = 0; i < 4; ++i)
	{
		if (this->_players[i])
			players->push_back(this->_players[i]);
	}
	Core::GameStateManager::get().pushState(
		*new GSInGame(*players, this->_mode, this->_map, this->_nbPlayers, _online));
}

bool	GSBindPlayer::isOnline() const
{
	return this->_online;
}

void	GSBindPlayer::addDemand(Core::GUICommand::PlayerType type)
{
	this->_demands.push_back(Demand(_id++, type));
}
