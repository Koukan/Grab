#include "TreeElement.hpp"
#include "Node.hpp"

TreeElement::TreeElement(void)
{
}


TreeElement::~TreeElement(void)
{
}

Node *TreeElement::getNode() const
{
	return (this->_node);
}

void TreeElement::setNode(Node *node)
{
	this->_node = node;
}
