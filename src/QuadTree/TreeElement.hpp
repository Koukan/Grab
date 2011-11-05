#pragma once

class Node;

class TreeElement
{
public:
	TreeElement(void);
	~TreeElement(void);

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getXCoord() = 0;
	virtual int getYCoord() = 0;

	Node *getNode() const;
	void setNode(Node *node);

private:
	Node	*_node;
};

