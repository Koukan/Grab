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
	void collide(TreeElement &elem);

	void display(Node *node, std::string const &space = "  ");
	void display(std::string const &space = "  ");

private:
	Node *_mainNode;

	Node	*createNode(TreeElement &elem);
	bool	isInSquare(TreeElement &elem, int x, int y, int size);
	Node	*findChild(Node *node, TreeElement &elem);
	void	insertChild(Node *node, TreeElement &elem);
	void	insertParent(TreeElement &elem);
	void	eraseNode(Node *node);
};

