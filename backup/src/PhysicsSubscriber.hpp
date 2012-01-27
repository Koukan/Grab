#ifndef		_PHYSICSSUBSCRIBER_
#define 	_PHYSICSSUBSCRIBER_

#include "IPhysicsSubscriber.hpp"

template <class T>
class PhysicsSubscriber : public IPhysicsSubscriber
{
  public:
    typedef void	(T::*MemFunc)(GameObject&, GameObject&);

    PhysicsSubscriber(T &object, MemFunc function) :
	    _object(object), _func(function)
    {
    }
    virtual ~PhysicsSubscriber(){}
    virtual void	operator()(GameObject &obj1, GameObject &obj2)
    {
        (_object.*_func)(obj1, obj2);
    }

  private:
    PhysicsSubscriber();

    T			&_object;
    MemFunc		_func;
};

#endif		/* _PHYSICSSUBSCRIBER_ */
