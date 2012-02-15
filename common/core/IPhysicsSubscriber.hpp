#ifndef		_IPHYSICSSUBSCRIBER_
#define 	_IPHYSICSSUBSCRIBER_

#include "GameObject.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ IPhysicsSubscriber
{
  public:
    virtual ~IPhysicsSubscriber(){}
    virtual void	operator()(GameObject&, GameObject&) = 0;
};

CORE_END_NAMESPACE

#endif		/* _IPHYSICSSUBSCRIBER_ */
