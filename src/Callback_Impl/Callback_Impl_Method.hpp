#ifndef		_CALLBACK_IMPL_METHOD_
#define 	_CALLBACK_IMPL_METHOD_

#include "Callback_Impl.hpp"

template <class InstanceClass>
class Callback_Impl_Method : public Callback_Impl
{
  public:
    Callback_Impl_Method(InstanceClass *instance, void (InstanceClass::*function)());
    virtual ~Callback_Impl_Method();
    virtual void	call();

  private:
    InstanceClass	*_instance;
    void		(InstanceClass::*_func)();
};

#include "Callback_Impl_Method.ipp"

#endif		/* _CALLBACK_IMPL_METHOD_ */
