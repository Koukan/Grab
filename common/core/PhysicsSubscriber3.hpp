#ifndef		_PHYSICSSUBSCRIBER3_
#define 	_PHYSICSSUBSCRIBER3_

#include "IPhysicsSubscriber.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ PhysicsSubscriber3 : public IPhysicsSubscriber
{
  public:
    PhysicsSubscriber3(void (*function)(GameObject&, GameObject&)) :
	    _func(function)
    {
    }
    virtual ~PhysicsSubscriber3(){}
    virtual void	operator()(GameObject &obj1, GameObject &obj2)
    {
        (*_func)(obj1, obj2);
    }

  private:
    PhysicsSubscriber3();

	void			(*_func)(GameObject&, GameObject&);
};

CORE_END_NAMESPACE

#endif		/* _PHYSICSSUBSCRIBER3_ */
