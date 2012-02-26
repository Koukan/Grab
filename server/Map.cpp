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

void		Map::addMonster(std::string const &name, size_t x, size_t y)
{
	Map::mapdata	data;
	data.name = name;
	data.x = x;
	_monsters.insert(std::make_pair(y, data));
}

void    	Map::addDecoration(std::string const &name, size_t x, size_t y)
{
	Map::mapdata	data;
	data.name = name;
	data.x = x;
	_decorations.insert(std::make_pair(y, data));
}

void		Map::move(double time)
{
	PhysicObject::move(time);
	GameCommand	*cmd;
	std::multimap<size_t, mapdata>::iterator it = _monsters.begin();
	for (; it != _monsters.end() && it->first <= this->_y; ++it)
	{
		cmd = new GameCommand("spawnmonster");
		cmd->y = this->_y - it->first; 
		cmd->x = it->second.x;
		cmd->data = it->second.name;
		Core::CommandDispatcher::get().pushCommand(*cmd);	
	}
	for (it = _decorations.begin(); it != _decorations.end() && it->first <= this->_y; ++it)
	{
		cmd = new GameCommand("spawdecoration");
		cmd->y = this->_y - it->first;
		cmd->x = it->second.x;
		cmd->data = it->second.name;
		Core::CommandDispatcher::get().pushCommand(*cmd);	
	}
}
