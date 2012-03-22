#include "GSBindPlayer.hpp"
#include "GSLoading.hpp"
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
		100, 1024, 300, 20, 100, "up arrow", "down arrow");
	layout->setY((RendererManager::get().getHeight() - layout->getHeight()) / 2);
	layout->setDispatch(true);

	Core::ButtonSprite *sprite = new Core::ButtonSprite("long button", "long button", "long button");

	for (unsigned int i = 0; i < this->_nbPlayers; ++i)
		_buttons.push_back(new GUIPlayerButton(*this, *(this->_players + i), this->_nbPending, this->_nbReady, *sprite, "buttonFont", layout, i));
}

bool	GSBindPlayer::handleCommand(Core::Command const &command)
{
	Method		tab[] = {
		{"answerBind", &GSBindPlayer::answerBind},
		{"updatePlayerPacket", &GSBindPlayer::updatePlayer},
		{"removePlayer", &GSBindPlayer::removePlayer},
		{"goToLoadGame", &GSBindPlayer::goToLoadGame}
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

void	GSBindPlayer::goToLoadGame(Core::Command const &)
{
	std::list<Player *> *players = new std::list<Player *>;

	for (int i = 0; i < 4; ++i)
	{
		if (this->_players[i])
			players->push_back(this->_players[i]);
	}
	Core::GameStateManager::get().pushState(*new GSLoading(*players, this->_mode, this->_map, this->_nbPlayers, this->_online));
}

void	GSBindPlayer::goToInGame()
{
	std::list<Player *> *players = new std::list<Player *>;
	size_t i = 0;

	for (; i < 4; ++i)
	{
		if (this->_players[i])
			players->push_back(this->_players[i]);
	}
	GSInGame	*state = new GSInGame(*players, this->_mode, this->_map, players->size(), this->_online);
	for (i = 0; i < 4; ++i)
	{
		if (this->_players[i] && this->_players[i]->getShip())
		{
				state->addGameObject(this->_players[i]->getShip(),
				(this->_players[i]->getType() != Player::ONLINE) ?
				"players" : "playersOnline");
		}
	}
	if (players->size() == 1 && this->_players[0])
	  this->_players[0]->setLife(3);
	state->preload();
	Core::GameStateManager::get().pushState(*state);
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
				this->_players[i] = new Player(static_cast<Player::type>(it->second));
				this->_players[i]->setShipInfo(&ShipInfo::shipsList[0]);
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
			delete this->_players[i];
			this->_players[i] = 0;
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
			this->_players[i]->setShipInfo(&ShipInfo::shipsList[cmd.idResource]);
			return ;
		}
		i++;
	}
}
