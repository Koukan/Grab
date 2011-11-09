#include "QuadTree.hpp"


QuadTree::QuadTree(void)
	: _mainNode(0)
{
}


QuadTree::~QuadTree(void)
{
}

bool	QuadTree::isInSquare(TreeElement &elem, int x, int y, int size) const
{
	return (elem.getXElement() >= x && elem.getXElement() + elem.getWidthElement() <= x + size &&
		elem.getYElement() >= y && elem.getYElement() + elem.getHeightElement() <= y + size);
}

Node	*QuadTree::createNode(TreeElement &elem) const
{
	int size = 1;

	if (elem.getWidthElement() > elem.getHeightElement())
	{
		while (size < elem.getWidthElement())
			size = size << 1;
	}
	else
	{
		while (size < elem.getHeightElement())
			size = size << 1;
	}
	int x = elem.getXElement() / size * size;
	int y = elem.getYElement() / size * size;
	while (!this->isInSquare(elem, x, y, size))
	{
		size = size << 1;
		x = elem.getXElement() / size * size;
		y = elem.getYElement() / size * size;
	}
	Node *node = new Node(x, y, size);
	node->getElements().insert(&elem);
	elem.setNode(node);
	return (node);
}

Node	*QuadTree::findChild(Node *node, TreeElement &elem) const
{
	Node *child = node->getChild(elem);

	if (child && this->isInSquare(elem, child->getX(), child->getY(), child->getSize()))
		return (child);
	return (0);
}

void	QuadTree::insertChild(Node *node, TreeElement &elem) const
{
	Node **childs = node->getChilds();
	int i = node->getChildPos(elem);

	if (this->isInSquare(elem,
		(i % 2) * (node->getSize() / 2) + node->getX(),
		(i / 2) * (node->getSize() / 2) + node->getY(), node->getSize() / 2))
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

void	QuadTree::insertOnTop(Node *node, TreeElement &elem)
{
	Node *parent;

	while ((parent = node->getParent()) && !this->isInSquare(elem, parent->getX(), parent->getY(), parent->getSize()))
		node = parent;
	if (parent)
	{
		Node *prev = parent;
		while ((parent = this->findChild(parent, elem)) != 0)
			prev = parent;
		parent = prev;
		this->insertChild(parent, elem);
	}
	else
	{
		this->insertParent(elem);
	}
}

void	QuadTree::push(TreeElement &elem)
{
	if (elem.getXElement() < 0 || elem.getYElement() < 0)
		return ;
	if (!this->_mainNode)
	{
		this->_mainNode = this->createNode(elem);
	}
	else
	{
		Node *node = this->_mainNode;
		if (this->isInSquare(elem, node->getX(), node->getY(), node->getSize()))
		{
			Node *prev = node;
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

Node	*QuadTree::eraseNode(Node *node)
{
	Node *parent = node->getParent();
	Node *child = node->getFirstChild();
	Node *ret = 0;

	if (!parent)
		this->_mainNode = child;
	else
	{
		int i = parent->getChildPos(node);

		parent->getChilds()[i] = child;
		ret = parent;
	}
	if (child)
	{
		child->setParent(parent);
		if (!parent)
			ret = child;
	}
	delete node;
	return (ret);
}

void	QuadTree::pop(TreeElement &elem)
{
	if (elem.getXElement() < 0 || elem.getYElement() < 0)
		return ;
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
	if (elem.getXElement() < 0 || elem.getYElement() < 0)
		return ;
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
				node = this->eraseNode(node);
				if (parent)
				{
					if (parent->getElements().empty() && parent->getNbChilds() == 1)
						node = this->eraseNode(parent);
				}
			}
			else
				node->getElements().erase(&elem);
		}
		if (!node)
			this->_mainNode = this->createNode(elem);
		else if (this->isInSquare(elem, node->getX(), node->getY(), node->getSize()))
		{
			Node *tmp = node;
			Node *prev = node;
			while ((tmp = this->findChild(tmp, elem)) != 0)
				prev = tmp;
			tmp = prev;
			this->insertChild(tmp, elem);
		}
		else
			this->insertOnTop(node, elem);
	}
}

bool	QuadTree::collideRect(TreeElement &elem, int x, int y, int width, int height) const
{
	return (elem.getXElement() > x - elem.getWidthElement() && elem.getXElement() < x + width &&
		elem.getYElement() > y - elem.getHeightElement() && elem.getYElement() < y + height);
}

void	QuadTree::collide(TreeElement &elem) const
{
	Node *node = this->_mainNode;
	if (node && this->collideRect(elem, node->getX(), node->getY(), node->getSize(), node->getSize()))
		this->collide(elem, node);
}

void	QuadTree::collide(TreeElement &elem, Node *currentNode) const
{
	for (Elements::const_iterator it = currentNode->getElements().begin(); it != currentNode->getElements().end(); ++it)
	{
		if (this->collideRect(elem, (*it)->getXElement(), (*it)->getYElement(), (*it)->getWidthElement(), (*it)->getHeightElement()))
		{
			elem.collide(**it);
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		Node *node = currentNode->getChilds()[i];
		if (node && this->collideRect(elem, node->getX(), node->getY(), node->getSize(), node->getSize()))
			this->collide(elem, node);
	}
}

void	QuadTree::display(std::string const &space) const
{
	if (this->_mainNode)
		this->display(this->_mainNode, space);
	else
		std::cout << space << "<vide>" << std::endl;
}

void	QuadTree::display(Node *node, std::string const &space) const
{
	if (!node)
		return ;
	std::cout << space << "Node (x = " << node->getX() << " y = " << node->getY() << " size = " << node->getSize() << ")" << std::endl;
	std::cout << space << "elements :" << std::endl;
	for (Elements::const_iterator it = node->getElements().begin(); it != node->getElements().end(); ++it)
	{
		std::cout << space << " | x = " << (*it)->getXElement() << " y = " << (*it)->getYElement() <<
			" width = " << (*it)->getWidthElement() << " height = " << (*it)->getHeightElement() << std::endl;
	}
	std::cout << space << "childs :" << std::endl;
	for (int i = 0; i < 4; ++i)
		display(node->getChilds()[i], space + "  ");
}
