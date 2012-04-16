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
	_dependencies.erase(node.getName());
	std::map<std::string, std::list<std::string> >::iterator cpy;
	for (std::map<std::string, std::list<std::string> >::iterator it = _dependencies.begin(); cpy != _dependencies.end();)
	{
		cpy = it++;
		for (std::list<std::string>::iterator elem = it->second.begin(); elem != it->second.end(); ++elem)
		{
			if (*elem == node.getName())
				elem = it->second.erase(elem);
		}
		if (it->second.empty())
		{	
			CompositeNode *tmp = new CompositeNode(*this, it->first, _state);
			_state.addGameObject(tmp, "monsters");
			_dependencies.erase(it);
		}		
	}
}

void	CompositeMaster::registerCompositeNode(CompositeNode &node, std::list<std::string> const &dependencies)
{
	_dependencies[node.getName()] = dependencies;	
}
