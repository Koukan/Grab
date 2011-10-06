#ifndef		_DRAWABLEOBJECT_
#define 	_DRAWABLEOBJECT_

#include "GameObject.hpp"

class DrawableObject : public GameObject
{
  public:
	  DrawableObject() {}
	  virtual ~DrawableObject() {}

	virtual void draw() = 0;
};

#endif		/* _DRAWABLEOBJECT_ */
