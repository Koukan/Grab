#ifndef		_CALLBACK_IMPL_METHOD_USERDATA_
#define 	_CALLBACK_IMPL_METHOD_USERDATA_

#include "Callback_Impl_UserData.hpp"
#include "Callback_Impl_Instance.hpp"

template <class InstanceClass, typename UserData>
class Callback_Impl_Method_UserData : public Callback_Impl, public Callback_Impl_UserData<UserData>, public Callback_Impl_Instance<InstanceClass>
{
  public:
    Callback_Impl_Method_UserData(void (InstanceClass::*function)(UserData&));
    Callback_Impl_Method_UserData(InstanceClass *instance,
		    void (InstanceClass::*function)(UserData&));
    Callback_Impl_Method_UserData(InstanceClass *instance,
		    void (InstanceClass::*function)(UserData&), UserData *data);
    virtual ~Callback_Impl_Method_UserData();
    virtual void	call();

  private:
    void		(InstanceClass::*_func)(UserData&);
};

#include "Callback_Impl_Method_UserData.ipp"

#endif		/* _CALLBACK_IMPL_METHOD_USERDATA_ */
