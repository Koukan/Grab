#include "Map.hpp"
#include "RectHitBox.hpp"
#include "GameCommand.hpp"
#include "CommandDispatcher.hpp"

Map::Map() : Core::PhysicObject(*new Core::RectHitBox(0, 0, 10, 10), 0, 100)
{}

Map::~Map()
{}

Core::Resource    *Map::clone() const
{
	return (new Map(*this));
}

void		Map::addMonster(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, int spawnY)
{
  this->addElem("spawnspawner", name, x, y, vx, vy, scrollable, spawnY);
}

void    	Map::addDecoration(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, int spawnY)
{
  this->addElem("spawndecoration", name, x, y, vx, vy, scrollable, spawnY);
}

void    	Map::addSound(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, int spawnY)
{
  this->addElem("spawnsound", name, x, y, vx, vy, scrollable, spawnY);
}

void    	Map::addElem(std::string const &command, std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, int spawnY)
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
		if (scrollable)
			data.vScrolling = this->_vy;
		else
			data.vScrolling = 0;
		_monsters.insert(std::make_pair(y, data));
	}
}

void		Map::move(double time)
{
	PhysicObject::move(time);
	GameCommand	*cmd;
	std::multimap<size_t, mapdata>::iterator it = _monsters.begin();
	for (; it != _monsters.end() && it->first <= this->_y;)
	{
		cmd = new GameCommand(it->second.command);
		cmd->y = this->_y - it->first + it->second.y;
		cmd->x = it->second.x;
		cmd->vx = it->second.vx;
		cmd->vy = it->second.vy;
		cmd->position = it->second.vScrolling;
		cmd->data = it->second.name;
		Core::CommandDispatcher::get().pushCommand(*cmd);
		_monsters.erase(it);
		it = _monsters.begin();
	}
}
