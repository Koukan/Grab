#ifndef		_IPHYSICSSUBSCRIBER_
#define 	_IPHYSICSSUBSCRIBER_

#include "GameObject.hpp"

class IPhysicsSubscriber
{
  public:
    virtual ~IPhysicsSubscriber(){}
    virtual void	operator()(GameObject&, GameObject&) = 0;
};

#endif		/* _IPHYSICSSUBSCRIBER_ */
