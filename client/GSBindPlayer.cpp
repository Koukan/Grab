#include "GSBindPlayer.hpp"
#include "GSInGame.hpp"
#include "GUIPlayerButton.hpp"
#include "GUIVLayout.hpp"
#include "GameStateManager.hpp"
#include "RendererManager.hpp"
#include "GameCommand.hpp"
#include "CommandDispatcher.hpp"

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
	this->load("resources/xml/intro.xml");

	// add gui

	Core::GUILayout *layout = new GUIVLayout(RendererManager::get().getWidth() / 2,
		(RendererManager::get().getHeight() - 100) / 2, 300, 300, 20, 100, "up arrow", "down arrow");
	layout->setY((RendererManager::get().getHeight() - layout->getHeight()) / 2);
	layout->setDispatch(true);

	Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");

	for (unsigned int i = 0; i < this->_nbPlayers; ++i)
		_buttons.push_back(new GUIPlayerButton(*this, *(this->_players + i), this->_nbPending, this->_nbReady, *sprite, "buttonFont", layout, i));
}

bool	GSBindPlayer::handleCommand(Core::Command const &command)
{
	Method		tab[] = {
		{"answerBind", &GSBindPlayer::answerBind},
		{"updatePlayerPacket", &GSBindPlayer::updatePlayer},
		{"removePlayer", &GSBindPlayer::removePlayer},
		{"goToInGame", &GSBindPlayer::goToInGame}
	};

	for (size_t i = 0; i < sizeof(tab) / sizeof(*tab); i++)
	{
		if (tab[i].name == command.name)
		{
			(this->*(tab[i].func))(command);
			return true;
		}
	}
	return false;
}

void	GSBindPlayer::goToInGame(Core::Command const &)
{
	this->goToInGame();
}

void	GSBindPlayer::goToInGame()
{
	std::list<Player *> *players = new std::list<Player *>;

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
	for (DemandMap::const_iterator it = this->_demands.begin();
		 it != this->_demands.end(); it++)
	{
		if (it->second == type)
			return ;
	}
	Core::CommandDispatcher::get().pushCommand(*new GameCommand("demandPlayer", _id));
	this->_demands[_id++] = type;
}

void	GSBindPlayer::answerBind(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const&>(command);
	DemandMap::iterator it = this->_demands.find(cmd.idObject);

	if (it != this->_demands.end())
	{
		uint32_t	i = 0;
		for (std::list<GUIPlayerButton*>::const_iterator lit = this->_buttons.begin();
			 lit != this->_buttons.end(); lit++)
		{
			if (i == cmd.idResource)
			{
				(*lit)->addPlayer(it->second);
				break ;
			}
			i++;
		}
		this->_demands.erase(it);
	}
}

void	GSBindPlayer::removePlayer(uint32_t nb, Core::GUICommand::PlayerType type)
{
	if (this->_online)
	{
		Core::CommandDispatcher::get().pushCommand(*new GameCommand("unBindPlayer", nb));
		this->_demands.erase(type);
	}
}

void	GSBindPlayer::removePlayer(Core::Command const &command)
{
	GameCommand const	&cmd = static_cast<GameCommand const&>(command);
	uint32_t			i = 0;

	for (std::list<GUIPlayerButton*>::const_iterator it = this->_buttons.begin();
		 it != this->_buttons.end(); it++)
	{
		if (i == cmd.idObject)
		{
			(*it)->changeToEmpty();
			return ;
		}
		i++;
	}
}

void	GSBindPlayer::updatePlayer(uint32_t nb, uint32_t ship, bool ready)
{
	if (this->_online)
	{
		GameCommand *cmd = new GameCommand("updatePlayer", nb, ship);
		cmd->boolean = ready;
		Core::CommandDispatcher::get().pushCommand(*cmd);
	}
}

void	GSBindPlayer::updatePlayer(Core::Command const &command)
{
	GameCommand const	&cmd = static_cast<GameCommand const&>(command);
	uint32_t			i = 0;

	for (std::list<GUIPlayerButton*>::const_iterator it = this->_buttons.begin();
		 it != this->_buttons.end(); it++)
	{
		if (i == cmd.idObject)
		{
			(*it)->updatePlayer(cmd.idResource, cmd.boolean);
			return ;
		}
		i++;
	}
}
