#ifndef		_PHYSICSSUBSCRIBER2_
#define 	_PHYSICSSUBSCRIBER2_

#include "IPhysicsSubscriber.hpp"

template <class T>
class PhysicsSubscriber2 : public IPhysicsSubscriber
{
  public:
    typedef void	(T::*MemFunc)(GameObject&);

    PhysicsSubscriber2(MemFunc function) :
	    _func(function)
    {
    }
    virtual ~PhysicsSubscriber2(){}
    virtual void	operator()(GameObject &obj1, GameObject &obj2)
    {
      T			*obj = dynamic_cast<T*>(&obj1);;

      if (obj)
      	(obj->*_func)(obj2);
      else
		std::cout << "Callback physic fail" << std::endl;
    }

  private:
    PhysicsSubscriber2();

    MemFunc	_func;
};

#endif		/* _PHYSICSSUBSCRIBER2_ */
