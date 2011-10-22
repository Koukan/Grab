#ifndef		_CALLBACK_IMPL_FUNCTION_USERDATA_
#define 	_CALLBACK_IMPL_FUNCTION_USERDATA_

#include "Callback_Impl_UserData.hpp"

template <typename UserData>
class Callback_Impl_Function_UserData : public Callback_Impl, public Callback_Impl_UserData<UserData>
{
  public:
    Callback_Impl_Function_UserData(void (*function)(UserData&));
    Callback_Impl_Function_UserData(void (*function)(UserData&), UserData &data);
    virtual ~Callback_Impl_Function_UserData();
    virtual void	call();

  private:
    void		(*_func)(UserData &data);
};

#include "Callback_Impl_Function_UserData.ipp"

#endif		/* _CALLBACK_IMPL_FUNCTION_USERDATA_ */
