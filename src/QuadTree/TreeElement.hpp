#pragma once

class Node;

class TreeElement
{
public:
	TreeElement(void);
	~TreeElement(void);

	virtual int getWidthElement() = 0;
	virtual int getHeightElement() = 0;
	virtual int getXElement() = 0;
	virtual int getYElement() = 0;
	virtual void collide(TreeElement &elem) = 0;

	Node *getNode() const;
	void setNode(Node *node);

private:
	Node	*_node;
};

