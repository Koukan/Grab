#pragma once

#include "CoreDef.hpp"

CORE_BEGIN_NAMESPACE

class Node;

class CORE_DLLREQ TreeElement
{
public:
	TreeElement(void);
	virtual ~TreeElement(void);

	virtual int getWidthElement() = 0;
	virtual int getHeightElement() = 0;
	virtual int getXElement() = 0;
	virtual int getYElement() = 0;
	virtual void collide(TreeElement &elem) = 0;

	Node		*getNode() const;
	int			getNodeNb() const;
	int			getXElementAbs();
	int			getYElementAbs();

	void		setNode(Node *node);
	void		setNodeNb(int nb);
	void		setXElementAbs();
	void		setYElementAbs();

private:
	Node	*_node;
	int		_nodeNb;
	int		_absX;
	int		_absY;
};

CORE_END_NAMESPACE
