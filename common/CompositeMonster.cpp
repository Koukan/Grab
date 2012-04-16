#include "CompositeMonster.hpp"
#include "BulletCommand.hpp"
#include "CompositeMaster.hpp"
#include "CompositeNode.hpp"

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
	CompositeMaster *master = new CompositeMaster(_bulletml, state);
	
	CompositeNode	*tmp;
	state.addGameObject(master, "spawner");
	for (std::list<CompositeMonsterProvider::monster>::iterator it = monsters.begin();
		 it != monsters.end(); ++it)
	{
		tmp = new CompositeNode(*master, (*it).name, (*it).bulletmlscript, state);
		tmp->setPosition((*it).x, (*it).y);
		master->registerCompositeNode(*tmp, (*it).depends);
	}
	return master;
}
