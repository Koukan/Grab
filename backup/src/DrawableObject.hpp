#ifndef		_DRAWABLEOBJECT_
#define 	_DRAWABLEOBJECT_

#include "GameObject.hpp"

class DrawableObject : public GameObject
{
public:
  DrawableObject(double x = 0, double y = 0) :
    GameObject(x, y){}
  virtual ~DrawableObject() {}

  virtual void		draw(double elapseTime) = 0;
};

#endif		/* _DRAWABLEOBJECT_ */
