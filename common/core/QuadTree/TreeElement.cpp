#include "TreeElement.hpp"
#include "Node.hpp"

TreeElement::TreeElement(void)
	: _node(0)
{
}


TreeElement::~TreeElement(void)
{
}

Node *TreeElement::getNode() const
{
	return (this->_node);
}

int			TreeElement::getNodeNb() const
{
	return (this->_nodeNb);
}

void		TreeElement::setNodeNb(int nb)
{
	this->_nodeNb = nb;
}

void TreeElement::setNode(Node *node)
{
	this->_node = node;
}

int			TreeElement::getXElementAbs()
{
	return (this->_absX);
}

int			TreeElement::getYElementAbs()
{
	return (this->_absY);
}

void		TreeElement::setXElementAbs()
{
	int x = this->getXElement();
	if (x < 0)
		this->_absX = -this->getXElement() - this->getWidthElement();
	else
		this->_absX = x;
}

void		TreeElement::setYElementAbs()
{
	int y = this->getYElement();
	if (y < 0)
		this->_absY = -this->getYElement() - this->getHeightElement();
	else
		this->_absY = y;
}
