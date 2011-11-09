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

	void display(Node *node, std::string const &space = "  ") const;
	void display(std::string const &space = "  ") const;

private:
	Node *_mainNode;

	Node	*createNode(TreeElement &elem) const;
	bool	isInSquare(TreeElement &elem, int x, int y, int size) const;
	Node	*findChild(Node *node, TreeElement &elem) const;
	void	insertChild(Node *node, TreeElement &elem) const;
	void	insertParent(TreeElement &elem);
	void	insertOnTop(Node *node, TreeElement &elem);
	Node	*eraseNode(Node *node);
	bool	collideRect(TreeElement &elem, int x, int y, int width, int height) const;
	void	collide(TreeElement &elem, Node *node) const;
};

