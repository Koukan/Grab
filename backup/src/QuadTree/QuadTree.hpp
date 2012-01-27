#pragma once

#include <string>
#include <iostream>
#include "Node.hpp"

class QuadTree
{
public:
	enum callInfo
	{
		LEFT = 1,
		RIGHT = 2,
		ALL = LEFT | RIGHT
	};

public:
	QuadTree(void);
	~QuadTree(void);

	void push(TreeElement &elem);
	void pop(TreeElement &elem);
	void move(TreeElement &elem);
	void collide(TreeElement &elem, QuadTree::callInfo call = QuadTree::ALL) const;
	void collide(QuadTree const &quadTree, QuadTree::callInfo call = QuadTree::ALL) const;
	void collide() const;

	void display(Node *node, std::string const &space = "  ") const;
	void display(std::string const &space = "  ") const;

private:
	Node *_mainNode;

	void	collideNodes(Node *node, Node *node2, QuadTree::callInfo call) const;
	Node	*collideNode(Node *node, Node *node2, QuadTree::callInfo call) const;
	void	collideBranches(TreeElement &elem, QuadTree::callInfo call) const;
	void	collideElements(Elements &elems, Elements &elems2, QuadTree::callInfo call) const;
	int		findNodeNb(TreeElement &elem) const;
	Node	*createNode(TreeElement &elem) const;
	bool	isInSquare(TreeElement &elem, int x, int y, int size) const;
	Node	*findChild(Node *node, TreeElement &elem) const;
	void	insertChild(Node *node, TreeElement &elem) const;
	void	insertParent(TreeElement &elem, int nodeNb);
	void	insertOnTop(Node *node, TreeElement &elem, int nodeNb);
	Node	*eraseNode(Node *node, int nodeNb);
	bool	collideRect(int x, int y, int width, int height, int x2, int y2, int width2, int height2) const;
	void	collide(TreeElement &elem, int x, int y, int width, int height, Node *node, QuadTree::callInfo call) const;
	bool	isInMiddle(TreeElement &elem) const;
	void	deleteNodes(Node *node);
};

