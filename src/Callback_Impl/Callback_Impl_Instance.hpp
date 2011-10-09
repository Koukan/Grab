#ifndef		_CALLBACK_IMPL_INSTANCE_
#define 	_CALLBACK_IMPL_INSTANCE_

#include "Callback_Impl.hpp"

template <class InstanceClass>
class Callback_Impl_Instance : public virtual Callback_Impl
{
  public:
    Callback_Impl_Instance(InstanceClass *instance = 0);
    virtual ~Callback_Impl_Instance();
    void		clearInstance();
    void		setInstance(InstanceClass *instance);

  protected:
    InstanceClass	*_instance;
    InstanceClass	*_mem;
};

#include "Callback_Impl_Instance.ipp"

#endif		/* _CALLBACK_IMPL_INSTANCE_ */
