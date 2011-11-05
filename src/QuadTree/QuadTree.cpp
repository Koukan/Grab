#include "QuadTree.hpp"


QuadTree::QuadTree(void)
	: _mainNode(0)
{
}


QuadTree::~QuadTree(void)
{
}

bool	QuadTree::isInSquare(TreeElement &elem, int x, int y, int size)
{
	return (elem.getXCoord() >= x && elem.getXCoord() + elem.getWidth() <= x + size &&
		elem.getYCoord() >= y && elem.getYCoord() + elem.getHeight() <= y + size);
}

Node	*QuadTree::createNode(TreeElement &elem)
{
	int size = 1;

	if (elem.getWidth() > elem.getHeight())
	{
		while (size < elem.getWidth())
			size = size << 1;
	}
	else
	{
		while (size < elem.getHeight())
			size = size << 1;
	}
	int x = elem.getXCoord() / size * size;
	int y = elem.getYCoord() / size * size;
	while (!this->isInSquare(elem, x, y, size))
	{
		size = size << 1;
		x = elem.getXCoord() / size * size;
		y = elem.getYCoord() / size * size;
	}
	Node *node = new Node(x, y, size);
	node->getElements().insert(&elem);
	elem.setNode(node);
	return (node);
}

Node	*QuadTree::findChild(Node *node, TreeElement &elem)
{
	Node *child = node->getChild(elem);

	if (child && this->isInSquare(elem, child->getX(), child->getY(), child->getSize()))
		return (child);
	return (0);
}

void	QuadTree::insertChild(Node *node, TreeElement &elem)
{
	Node **childs = node->getChilds();
	int i = node->getChildPos(elem);

	if (this->isInSquare(elem, (i % 2) * (node->getSize() / 2), (i / 2) * (node->getSize() / 2), node->getSize() / 2))
	{
		if (childs[i])
		{
			int size = childs[i]->getSize() * 2;
			int x = childs[i]->getX() / size * size;
			int y = childs[i]->getY() / size * size;
			while (!this->isInSquare(elem, x, y, size))
			{
				size = size * 2;
				x = x / size * size;
				y = y / size * size;
			}
			Node *child = new Node(x, y, size);
			child->setChild(childs[i]);
			childs[i]->setParent(child);
			childs[i] = child;
			child->setParent(node);
			this->insertChild(child, elem);
		}
		else
		{
			childs[i] = this->createNode(elem);
			childs[i]->setParent(node);
		}
	}
	else
	{
		node->getElements().insert(&elem);
		elem.setNode(node);
	}
}

void	QuadTree::insertParent(TreeElement &elem)
{
	int size = this->_mainNode->getSize() * 2;
	int x = this->_mainNode->getX() / size * size;
	int y = this->_mainNode->getY() / size * size;
	while (!this->isInSquare(elem, x, y, size))
	{
		size = size * 2;
		x = x / size * size;
		y = y / size * size;
	}
	Node *child = new Node(x, y, size);
	child->setChild(this->_mainNode);
	this->_mainNode->setParent(child);
	this->_mainNode = child;
	this->insertChild(child, elem);
}

void	QuadTree::push(TreeElement &elem)
{
	if (!this->_mainNode)
	{
		this->_mainNode = this->createNode(elem);
	}
	else
	{
		Node *node = this->_mainNode;
		Node *prev = node;
		if (this->isInSquare(elem, node->getX(), node->getY(), node->getSize()))
		{
			prev = node;
			while ((node = this->findChild(node, elem)) != 0)
				prev = node;
			node = prev;
			this->insertChild(node, elem);
		}
		else
		{
			this->insertParent(elem);
		}
	}
}

void	QuadTree::eraseNode(Node *node)
{
	Node *parent = node->getParent();
	Node *child = node->getFirstChild();

	if (!parent)
		this->_mainNode = child;
	else
	{
		int i = parent->getChildPos(node);

		parent->getChilds()[i] = child;
	}
	if (child)
		child->setParent(parent);
	delete node;
}

void	QuadTree::pop(TreeElement &elem)
{
	Node *node = elem.getNode();
	if (node)
	{
		if (node->getElements().size() > 1)
			node->getElements().erase(&elem);
		else
		{
			int nbChilds = node->getNbChilds();
			if (nbChilds < 2)
			{
				Node *parent = node->getParent();
				this->eraseNode(node);
				if (parent)
				{
					if (parent->getElements().empty() && parent->getNbChilds() == 1)
						this->eraseNode(parent);
				}
			}
			else
				node->getElements().erase(&elem);
		}
	}
}

void	QuadTree::move(TreeElement &elem)
{
}

void	QuadTree::collide(TreeElement &elem)
{
	if (this->_mainNode)
	{
	}
}

void	QuadTree::display(std::string const &space)
{
	this->display(this->_mainNode, space);
}

void	QuadTree::display(Node *node, std::string const &space)
{
	if (!node)
		return ;
	std::cout << space << "Node (x = " << node->getX() << " y = " << node->getY() << " size = " << node->getSize() << ")" << std::endl;
	std::cout << space << "elements :" << std::endl;
	for (Elements::const_iterator it = node->getElements().begin(); it != node->getElements().end(); ++it)
	{
		std::cout << space << " | x = " << (*it)->getXCoord() << " y = " << (*it)->getYCoord() <<
			" width = " << (*it)->getWidth() << " height = " << (*it)->getHeight() << std::endl;
	}
	std::cout << space << "childs :" << std::endl;
	for (int i = 0; i < 4; ++i)
		display(node->getChilds()[i], space + "  ");
}
