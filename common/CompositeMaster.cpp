#include "CompositeMaster.hpp"
#include "CompositeNode.hpp"

CompositeMaster::CompositeMaster(std::string const &script, Core::GameState &gstate) :
	Core::BulletCommand(script, gstate), _state(gstate)
{
}

CompositeMaster::~CompositeMaster()
{}

void    CompositeMaster::notifyDeath(CompositeNode &node)
{
	_dependencies.erase(&node);
	std::map<CompositeNode*, std::list<std::string> >::iterator it;
	for (std::map<CompositeNode*, std::list<std::string> >::iterator cpy = _dependencies.begin(); cpy != _dependencies.end();)
	{
		it = cpy++;
		for (std::list<std::string>::iterator elem = it->second.begin(); elem != it->second.end(); ++elem)
		{
			if (*elem == node.getName())
				elem = it->second.erase(elem);
		}
		if (it->second.empty())
		{	
			_state.addGameObject(it->first, "monsters");
			it->first->setLink(this);
			_dependencies.erase(it);
		}	
	}
}

void	CompositeMaster::registerCompositeNode(CompositeNode &node, std::list<std::string> const &dependencies)
{
	if (dependencies.empty())
	{
		_state.addGameObject(&node, "monsters");
		node.setLink(this);
	}
	else
		_dependencies[&node] = dependencies;
}
