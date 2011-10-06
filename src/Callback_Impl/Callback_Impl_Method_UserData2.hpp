#ifndef		_CALLBACK_IMPL_METHOD_USERDATA2_
#define 	_CALLBACK_IMPL_METHOD_USERDATA2_

#include "Callback_Impl_UserData2.hpp"

template <class InstanceClass, typename UserData1, typename UserData2>
class Callback_Impl_Method_UserData2 : public Callback_Impl_UserData2<UserData1, UserData2>
{
  public:
    Callback_Impl_Method_UserData2(InstanceClass *instance,
		    void (InstanceClass::*function)(UserData1&, UserData2&));
    Callback_Impl_Method_UserData2(InstanceClass *instance,
		    void (InstanceClass::*function)(UserData1&, UserData2&),
		    	  UserData1 *data1, UserData2 *data2);
    virtual ~Callback_Impl_Method_UserData2();
    virtual void	call();

  private:
    InstanceClass	*_instance;
    void		(InstanceClass::*_func)(UserData1&, UserData2&);
};

#include "Callback_Impl_Method_UserData2.ipp"

#endif		/* _CALLBACK_IMPL_METHOD_USERDATA2_ */
