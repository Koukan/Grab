#include "GSLoading.hpp"
#include "GSInGame.hpp"
#include "GameCommand.hpp"
#include "GameStateManager.hpp"
#include "CommandDispatcher.hpp"

GSLoading::GSLoading(std::list<Player *> const &players, Modes::Mode mode,
		std::string const &map, unsigned int nbPlayers, bool online)
	: Core::GameState("Loading"), _players(players), _nbPlayers(nbPlayers), _nbShip(0),
	  _game(*new GSInGame(players, mode, map, nbPlayers, online))
{
}

GSLoading::~GSLoading()
{
}

void		GSLoading::onStart()
{
	_game.preload();
}

bool		GSLoading::handleCommand(Core::Command const &command)
{
	Method<std::string>	tab[] = {
		{"goToInGame", &GSLoading::goToInGame},
		{"shipSpawn", &GSLoading::shipSpawn}
	};

	for (size_t i = 0; i < sizeof(tab) / sizeof(*tab); i++)
	{
		if (tab[i].name == command.name)
		{
			(this->*(tab[i].method))(command);
			return true;
		}
	}
	return false;
}

void		GSLoading::goToInGame(Core::Command const &)
{
	Core::GameStateManager::get().changeState(_game);
}

void		GSLoading::shipSpawn(Core::Command const &command)
{
  // player colors
  static struct {
    int r;
    int g;
    int b;
  } playerColors[] =
      {
	{255, 0, 0},
	{0, 255, 0},
	{0, 0, 255},
	{255, 255, 0}
      };

	GameCommand	const		&cmd = static_cast<GameCommand const &>(command);
	uint32_t				i = 0;

	for (std::list<Player*>::const_iterator it = this->_players.begin();
		 it != this->_players.end(); it++)
	{
		if (cmd.idResource == i)
		{
			Ship::ShipInfo const	*info;
			Ship					*ship;
			info = (*it)->getShipInfo();
			ship = new Ship(*info, playerColors[i].r, playerColors[i].g,
				playerColors[i].b);
			ship->setX(cmd.x);
			ship->setY(cmd.y);
			ship->setId(cmd.idObject);
			if (!(*it)->getShip())
				this->_nbShip++;
			(*it)->setShip(ship);
			if ((*it)->getType() != Player::type::ONLINE)
				this->_game.addGameObject(ship, "players");
			else
				this->_game.addGameObject(ship, "playersOnline");
			if (this->_nbShip == this->_nbPlayers)
				Core::CommandDispatcher::get().pushCommand(*new Core::Command("Ready"));
			return ;
		}
		i++;
	}
}
