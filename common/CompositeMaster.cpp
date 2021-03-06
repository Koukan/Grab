#include "CompositeMaster.hpp"
#include "CompositeNode.hpp"

CompositeMaster::CompositeMaster(std::string const &script, Core::GameState &gstate) :
	Core::BulletCommand(script, gstate), _state(gstate), _count(0), _bullet(0)
{
}

CompositeMaster::~CompositeMaster()
{}

void    CompositeMaster::createBullet(BulletMLState* state, double direction, double speed)
{	
	_bullet = this->instantiateBullet(state, direction, speed);
	_bullet->setCollidable(false);
	for (std::list<CompositeNode*>::iterator it = _toadd.begin(); it != _toadd.end(); ++it)
		(*it)->begin();
	this->_toadd.clear();
}

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
			it->first->start();
			_dependencies.erase(it);
		}	
	}
	_count--;
	if (_count == 0)
	{
		_bullet->setCollidable(true);
		this->erase();
	}
}

void	CompositeMaster::registerCompositeNode(CompositeNode &node, std::list<std::string> const &dependencies)
{
	_state.addGameObject(&node, "spawner");
	if (!dependencies.empty())
		_dependencies[&node] = dependencies;
	else
		_toadd.push_back(&node);
	_count++;
}

Core::BulletCommand *CompositeMaster::getBullet() const
{
	return _bullet;
}
