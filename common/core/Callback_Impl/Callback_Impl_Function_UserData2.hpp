#ifndef		_CALLBACK_IMPL_FUNCTION_USERDATA2_
#define 	_CALLBACK_IMPL_FUNCTION_USERDATA2_

#include "Callback_Impl_UserData2.hpp"

template <typename UserData1, typename UserData2>
class Callback_Impl_Function_UserData2 : public Callback_Impl_UserData2<UserData1, UserData2>
{
  public:
    Callback_Impl_Function_UserData2(void (*function)(UserData1&, UserData2&));
    Callback_Impl_Function_UserData2(void (*function)(UserData1&, UserData2&),
		    		    UserData1 &data1, UserData2 &data2);
    virtual ~Callback_Impl_Function_UserData2();
    virtual void	call();

  private:
    void		(*_func)(UserData1 &data1, UserData2 &data2);
};

#include "Callback_Impl_Function_UserData2.ipp"

#endif		/* _CALLBACK_IMPL_FUNCTION_USERDATA2_ */
