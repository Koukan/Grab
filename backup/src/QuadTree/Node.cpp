#include "Node.hpp"


Node::Node(int x, int y, int size)
	: _parent(0), _size(size), _x(x), _y(y)
{
	this->_childs[0] = 0;
	this->_childs[1] = 0;
	this->_childs[2] = 0;
	this->_childs[3] = 0;
}

Node::~Node(void)
{
}

Node	**Node::getChilds()
{
	return (this->_childs);
}

Node	*Node::getChild(TreeElement &elem)
{
	int size = this->_size / 2;
	int x = (elem.getXElementAbs() - this->_x) / size;
	int y = (elem.getYElementAbs() - this->_y) / size;
	int i = x + y * 2;

	return (this->_childs[i]);
}

int		Node::getChildPos(TreeElement &elem)
{
	int size = this->_size / 2;
	int x = (elem.getXElementAbs() - this->_x) / size;
	int y = (elem.getYElementAbs() - this->_y) / size;
	int i = x + y * 2;

	return (i);
}

int			Node::getChildPos(Node *node)
{
	int size = this->_size / 2;
	int x = (node->getX() - this->_x) / size;
	int y = (node->getY() - this->_y) / size;
	int i = x + y * 2;

	return (i);
}

void		Node::setChild(Node *node)
{
	int size = this->_size / 2;
	int x = (node->getX() - this->_x) / size;
	int y = (node->getY() - this->_y) / size;
	int i = x + y * 2;

	this->_childs[i] = node;
}

Node	*Node::getParent()
{
	return (this->_parent);
}

void	Node::setParent(Node *node)
{
	this->_parent = node;
}

Elements &Node::getElements()
{
	return (this->_elements);
}

int			Node::getSize() const
{
	return (this->_size);
}

void		Node::setSize(int size)
{
	this->_size = size;
}

int			Node::getX() const
{
	return (this->_x);
}

void		Node::setX(int x)
{
	this->_x = x;
}

int			Node::getY() const
{
	return (this->_y);
}

void		Node::setY(int y)
{
	this->_y = y;
}

int			Node::getNbChilds() const
{
	int i = 0;

	for (int j = 0; j < 4; ++j)
	{
		if (this->_childs[j])
			++i;
	}
	return (i);
}

Node		*Node::getFirstChild()
{
	for (int i = 0; i < 4; ++i)
	{
		if (this->_childs[i])
			return (this->_childs[i]);
	}
	return (0);
}
