#ifndef		_DRAWABLEOBJECT_
#define 	_DRAWABLEOBJECT_

#include "GameObject.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ DrawableObject : public GameObject
{
public:
  DrawableObject(double x = 0, double y = 0) :
    GameObject(x, y){}
  virtual ~DrawableObject() {}

  virtual void		draw(double elapseTime) = 0;
};


CORE_END_NAMESPACE

#endif		/* _DRAWABLEOBJECT_ */
