#pragma once

#include <set>
#include "TreeElement.hpp"

typedef std::set<TreeElement *>	Elements;

class Node
{
public:
	Node(int x, int y, int size);
	~Node(void);

	Node		**getChilds();
	Node		*getChild(TreeElement &elem);
	Node		*getFirstChild();
	void		setChild(Node *node);
	int			getChildPos(TreeElement &elem);
	int			getChildPos(Node *node);
	Node		*getParent();
	void		setParent(Node *node);
	Elements	&getElements();
	int			getSize() const;
	void		setSize(int size);
	int			getX() const;
	void		setX(int x);
	int			getY() const;
	void		setY(int y);
	int			getNbChilds() const;

private:
	Node	*_childs[4];
	Node	*_parent;
	Elements _elements;
	int		_size;
	int		_x;
	int		_y;
};

