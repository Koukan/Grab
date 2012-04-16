#include "CompositeNode.hpp"
#include "CompositeMaster.hpp"

CompositeNode::CompositeNode(CompositeMaster &parent, std::string const &name, std::string const &script, Core::GameState &gstate) : Core::BulletCommand(script, gstate), _parent(parent), _name(name)
{}

CompositeNode::~CompositeNode()
{}

void	CompositeNode::erase()
{
	if (_childs.empty())
		_parent.notifyDeath(*this);
	this->Core::BulletCommand::erase();
}

std::string const &CompositeNode::getName()
{
	return _name;
}
