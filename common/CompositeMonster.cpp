#include "CompositeMonster.hpp"
#include "BulletCommand.hpp"

CompositeMonster::CompositeMonster(std::string const &script) : _bulletml(script)
{}

CompositeMonster::~CompositeMonster()
{}

Core::Resource    *CompositeMonster::clone() const
{
	return (new CompositeMonster(*this));
}

void    	CompositeMonster::addMonster(CompositeMonsterProvider::monster &m)
{
	monsters.push_back(m);
}

Core::BulletCommand	*CompositeMonster::getBulletCommand(Core::GameState &state)
{
	Core::BulletCommand *master = new Core::BulletCommand(_bulletml, state);
	
	Core::BulletCommand *tmp;
	state.addGameObject(master, "monsters");
	for (std::list<CompositeMonsterProvider::monster>::iterator it = monsters.begin();
		 it != monsters.end(); ++it)
	{
		tmp = new Core::BulletCommand((*it).bulletmlscript, state);
tmp->setPosition((*it).x, (*it).y);
		tmp->setLink(master);
		if ((*it).depends.empty())
			state.addGameObject(tmp, "monsters");
	}
	return master;
}
