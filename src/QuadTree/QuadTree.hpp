#pragma once

#include <string>
#include <iostream>
#include "Node.hpp"

class QuadTree
{
public:
	QuadTree(void);
	~QuadTree(void);

	void push(TreeElement &elem);
	void pop(TreeElement &elem);
	void move(TreeElement &elem);
	void collide(TreeElement &elem) const;
	void collide(QuadTree const &quadTree) const;
	void collide() const;

	void display(Node *node, std::string const &space = "  ") const;
	void display(std::string const &space = "  ") const;

private:
	Node *_mainNode;

	void	collideNodes(Node *node, Node *node2, QuadTree const &quadtree) const;
	Node	*collideNode(Node *node, Node *node2) const;
	void	collideElementsNode(Elements &elems, Node *node) const;
	void	collideElements(Elements &elems, Elements &elems2) const;
	int		findNodeNb(TreeElement &elem) const;
	Node	*createNode(TreeElement &elem) const;
	bool	isInSquare(TreeElement &elem, int x, int y, int size) const;
	Node	*findChild(Node *node, TreeElement &elem) const;
	void	insertChild(Node *node, TreeElement &elem) const;
	void	insertParent(TreeElement &elem, int nodeNb);
	void	insertOnTop(Node *node, TreeElement &elem, int nodeNb);
	Node	*eraseNode(Node *node, int nodeNb);
	bool	collideRect(int x, int y, int width, int height, int x2, int y2, int width2, int height2) const;
	void	collide(TreeElement &elem, int x, int y, int width, int height, Node *node) const;
	bool	isInMiddle(TreeElement &elem) const;
};

