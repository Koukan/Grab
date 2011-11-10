#include "QuadTree.hpp"


QuadTree::QuadTree(void)
	: _mainNode(new Node(0, 0, 0))
{
}


QuadTree::~QuadTree(void)
{
}

bool	QuadTree::isInSquare(TreeElement &elem, int x, int y, int size) const
{
	return (elem.getXElementAbs() >= x && elem.getXElementAbs() + elem.getWidthElement() <= x + size &&
		elem.getYElementAbs() >= y && elem.getYElementAbs() + elem.getHeightElement() <= y + size);
}

bool	QuadTree::isInMiddle(TreeElement &elem) const
{
	return ((elem.getXElement() < 0 && elem.getXElement() + elem.getWidthElement() > 0) ||
		(elem.getYElement() < 0 && elem.getYElement() + elem.getHeightElement() > 0));
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
	int x = elem.getXElementAbs() / size * size;
	int y = elem.getYElementAbs() / size * size;
	while (!this->isInSquare(elem, x, y, size))
	{
		size = size << 1;
		x = elem.getXElementAbs() / size * size;
		y = elem.getYElementAbs() / size * size;
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

void	QuadTree::insertParent(TreeElement &elem, int nodeNb)
{
	int size = this->_mainNode->getChilds()[nodeNb]->getSize() * 2;
	int x = this->_mainNode->getChilds()[nodeNb]->getX() / size * size;
	int y = this->_mainNode->getChilds()[nodeNb]->getY() / size * size;
	while (!this->isInSquare(elem, x, y, size))
	{
		size = size * 2;
		x = x / size * size;
		y = y / size * size;
	}
	Node *child = new Node(x, y, size);
	child->setChild(this->_mainNode->getChilds()[nodeNb]);
	this->_mainNode->getChilds()[nodeNb]->setParent(child);
	this->_mainNode->getChilds()[nodeNb] = child;
	this->insertChild(child, elem);
}

void	QuadTree::insertOnTop(Node *node, TreeElement &elem, int nodeNb)
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
		this->insertParent(elem, nodeNb);
	}
}

int		QuadTree::findNodeNb(TreeElement &elem) const
{
	int signx = elem.getXElement() >> 31 & 1;
	int signy = elem.getYElement() >> 31 & 1;

	return (signx + 2 * signy);
}

void	QuadTree::push(TreeElement &elem)
{
	if (this->isInMiddle(elem))
	{
		this->_mainNode->getElements().insert(&elem);
		elem.setNode(this->_mainNode);
		return ;
	}
	elem.setXElementAbs();
	elem.setYElementAbs();
	int nodeNb = this->findNodeNb(elem);
	elem.setNodeNb(nodeNb);
	if (!this->_mainNode->getChilds()[nodeNb])
		this->_mainNode->getChilds()[nodeNb] = this->createNode(elem);
	else
	{
		Node *node = this->_mainNode->getChilds()[nodeNb];
		if (this->isInSquare(elem, node->getX(), node->getY(), node->getSize()))
		{
			Node *prev = node;
			while ((node = this->findChild(node, elem)) != 0)
				prev = node;
			node = prev;
			this->insertChild(node, elem);
		}
		else
			this->insertParent(elem, nodeNb);
	}
}

Node	*QuadTree::eraseNode(Node *node, int nodeNb)
{
	Node *parent = node->getParent();
	Node *child = node->getFirstChild();
	Node *ret = 0;

	if (!parent)
		this->_mainNode->getChilds()[nodeNb] = child;
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
	int nodeNb = this->findNodeNb(elem);
	Node *node = elem.getNode();
	if (node)
	{
		if (node == this->_mainNode)
			this->_mainNode->getElements().erase(&elem);
		else
		{
			if (node->getElements().size() > 1)
				node->getElements().erase(&elem);
			else
			{
				int nbChilds = node->getNbChilds();
				if (nbChilds < 2)
				{
					Node *parent = node->getParent();
					this->eraseNode(node, nodeNb);
					if (parent)
					{
						if (parent->getElements().empty() && parent->getNbChilds() == 1)
							this->eraseNode(parent, nodeNb);
					}
				}
				else
					node->getElements().erase(&elem);
			}
		}
	}
}

void	QuadTree::move(TreeElement &elem)
{
	Node *node = elem.getNode();
	if (node)
	{
		if (node == this->_mainNode)
		{
			this->_mainNode->getElements().erase(&elem);
			this->push(elem);
		}
		else
		{
			if (node->getElements().size() > 1)
				node->getElements().erase(&elem);
			else
			{
				int nbChilds = node->getNbChilds();
				if (nbChilds < 2)
				{
					Node *parent = node->getParent();
					node = this->eraseNode(node, elem.getNodeNb());
					if (parent)
					{
						if (parent->getElements().empty() && parent->getNbChilds() == 1)
							node = this->eraseNode(parent, elem.getNodeNb());
					}
				}
				else
					node->getElements().erase(&elem);
			}
			int nodeNb = this->findNodeNb(elem);

			if (this->isInMiddle(elem))
			{
				this->_mainNode->getElements().insert(&elem);
				elem.setNode(this->_mainNode);
			}
			else if (elem.getNodeNb() != nodeNb)
				this->push(elem);
			else
			{
				elem.setXElementAbs();
				elem.setYElementAbs();
				if (!node)
					this->_mainNode->getChilds()[nodeNb] = this->createNode(elem);
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
					this->insertOnTop(node, elem, nodeNb);
			}
		}
	}
}

bool	QuadTree::collideRect(int x, int y, int width, int height, int x2, int y2, int width2, int height2) const
{
	return (x > x2 - width && x < x2 + width2 &&
		y > y2 - height && y < y2 + height2);
}

void	QuadTree::collide(TreeElement &elem) const
{
	for (Elements::const_iterator it = this->_mainNode->getElements().begin(); it != this->_mainNode->getElements().end(); ++it)
	{
		if (this->collideRect(elem.getXElement(), elem.getYElement(), elem.getWidthElement(), elem.getHeightElement(),
			(*it)->getXElement(), (*it)->getYElement(), (*it)->getWidthElement(), (*it)->getHeightElement()))
		{
			elem.collide(**it);
		}
	}
	Node **node = this->_mainNode->getChilds();
	if (node[0] && elem.getXElement() + elem.getWidthElement() > 0 && elem.getYElement() + elem.getHeightElement() > 0)
	{
		int x;
		int y;
		int width = elem.getWidthElement();
		int height = elem.getHeightElement();
		if (elem.getXElement() < 0)
		{
			x = 0;
			width += elem.getXElement();
		}
		else
			x = elem.getXElement();
		if (elem.getYElement() < 0)
		{
			y = 0;
			height += elem.getYElement();
		}
		else
			y = elem.getYElement();
		this->collide(elem, x, y, width, height, node[0]);
	}
	if (node[1] && elem.getXElement() < 0 && elem.getYElement() + elem.getHeightElement() > 0)
	{
		int x;
		int y;
		int width = elem.getWidthElement();
		int height = elem.getHeightElement();
		if (elem.getXElement() + elem.getWidthElement() > 0)
		{
			width -= elem.getXElement() + elem.getWidthElement();
			x = 0;
		}
		else
			x = -elem.getXElement() - elem.getWidthElement();
		if (elem.getYElement() < 0)
		{
			y = 0;
			height += elem.getYElement();
		}
		else
			y = elem.getYElement();
		this->collide(elem, x, y, width, height, node[1]);
	}
	if (node[2] && elem.getXElement() + elem.getWidthElement() > 0 && elem.getYElement() < 0)
	{
		int x;
		int y;
		int width = elem.getWidthElement();
		int height = elem.getHeightElement();
		if (elem.getXElement() < 0)
		{
			x = 0;
			width += elem.getXElement();
		}
		else
			x = elem.getXElement();
		if (elem.getYElement() + elem.getHeightElement() > 0)
		{
			height -= elem.getYElement() + elem.getHeightElement();
			y = 0;
		}
		else
			y = -elem.getYElement() - elem.getHeightElement();
		this->collide(elem, x, y, width, height, node[2]);
	}
	if (node[3] && elem.getXElement() < 0 && elem.getYElement() < 0)
	{
		int x;
		int y;
		int width = elem.getWidthElement();
		int height = elem.getHeightElement();
		if (elem.getXElement() + elem.getWidthElement() > 0)
		{
			width -= elem.getXElement() + elem.getWidthElement();
			x = 0;
		}
		else
			x = -elem.getXElement() - elem.getWidthElement();
		if (elem.getYElement() + elem.getHeightElement() > 0)
		{
			height -= elem.getYElement() + elem.getHeightElement();
			y = 0;
		}
		else
			y = -elem.getYElement() - elem.getHeightElement();
		this->collide(elem, x, y, width, height, node[3]);
	}
}

void	QuadTree::collide(TreeElement &elem, int x, int y, int width, int height, Node *currentNode) const
{
	for (Elements::const_iterator it = currentNode->getElements().begin(); it != currentNode->getElements().end(); ++it)
	{
		if (this->collideRect(x, y, width, height, (*it)->getXElementAbs(), (*it)->getYElementAbs(), (*it)->getWidthElement(), (*it)->getHeightElement()))
		{
			elem.collide(**it);
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		Node *node = currentNode->getChilds()[i];
		if (node && this->collideRect(x, y, width, height, node->getX(), node->getY(), node->getSize(), node->getSize()))
			this->collide(elem, x, y, width, height, node);
	}
}

void	QuadTree::display(std::string const &space) const
{
	Node *node = this->_mainNode;
	std::cout << space << "Main node :" << std::endl;
	std::cout << space << "elements :" << std::endl;
	for (Elements::const_iterator it = node->getElements().begin(); it != node->getElements().end(); ++it)
	{
		std::cout << space << " | x = " << (*it)->getXElement() << " y = " << (*it)->getYElement() <<
			" width = " << (*it)->getWidthElement() << " height = " << (*it)->getHeightElement() << std::endl;
	}
	for (int i = 0; i < 4; ++i)
	{
		if (this->_mainNode->getChilds()[i])
			this->display(this->_mainNode->getChilds()[i], space);
		else
			std::cout << space << "<vide>" << std::endl;
	}
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
