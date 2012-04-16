#include "CompositeNode.hpp"
#include "CompositeMaster.hpp"

CompositeNode::CompositeNode(CompositeMaster &parent, std::string const &script, Core::GameState &gstate) : Core::BulletCommand(script, gstate), _parent(parent), _name(script)
{}

CompositeNode::~CompositeNode()
{}

void	CompositeNode::erase()
{
	this->Core::BulletCommand::erase();
	_parent.notifyDeath(*this);
}

std::string const &CompositeNode::getName()
{
	return _name;
}
