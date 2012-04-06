#include "Map.hpp"
#include "RectHitBox.hpp"
#include "GameCommand.hpp"
#include "CommandDispatcher.hpp"
#include "GameState.hpp"

Map::Map() : Core::PhysicObject(*new Core::RectHitBox(0, 0, 10, 10), 0, 100), _nbPaused(0), _prevY(0)
{}

Map::~Map()
{
	
}

Core::Resource    *Map::clone() const
{
	return (new Map(*this));
}

void		Map::addEnd(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry)
{
  this->addElem("spawnend", name, x, y, vx, vy, scrollable, pause, spawnY, ry);
}

void		Map::addMonster(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry)
{
  this->addElem("spawnspawner", name, x, y, vx, vy, scrollable, pause, spawnY, ry);
}

void    	Map::addDecoration(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry)
{
  this->addElem("spawndecoration", name, x, y, vx, vy, scrollable, pause, spawnY, ry);
}

void    	Map::addSound(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry)
{
  this->addElem("spawnsound", name, x, y, vx, vy, scrollable, pause, spawnY, ry);
}

void    	Map::addElem(std::string const &command, std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry)
{
	if (y >= this->_y)
	{
		Map::mapdata	data;
		data.command = command;
		data.name = name;
		data.x = x;
		data.y = spawnY;
		data.vx = vx;
		data.vy = vy;
		data.pause = pause;
		if (scrollable)
			data.vScrolling = static_cast<int>(this->_vy);
		else
			data.vScrolling = 0;
		this->_prevY += ry;
		this->_monsters.insert(std::make_pair((y) ? y : this->_prevY, data));
	}
}

void		Map::move(double time)
{
  if (this->_nbPaused == 0)
    {
	PhysicObject::move(time);

	GameCommand	*cmd;
	Core::GameState	&gm = this->getGroup()->getState();
	for (std::multimap<size_t, mapdata>::iterator it = _monsters.begin();
				   	it != _monsters.end() && it->first <= this->_y;)
	{
		cmd = new GameCommand(it->second.command);
		cmd->y = static_cast<int16_t>(this->_y - it->first + it->second.y);
		cmd->x = it->second.x;
		cmd->vx = it->second.vx;
		cmd->vy = it->second.vy;
		cmd->position = static_cast<float>(it->second.vScrolling);
		cmd->data = it->second.name;
		cmd->boolean = it->second.pause;
		gm.pushCommand(*cmd, true);
		_monsters.erase(it);
		it = _monsters.begin();
	}
    }
}

void		Map::decreasePaused()
{
  --this->_nbPaused;
}

void		Map::increasePaused()
{
  ++this->_nbPaused;
}

void		Map::setScrollingSpeed(double vy)
{
	this->_vy = vy;
}
