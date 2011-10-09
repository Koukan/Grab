#include <iostream>
template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::
	Callback_Impl_Method_UserData(
	void (InstanceClass::*function)(UserData&))
	: Callback_Impl(), Callback_Impl_UserData<UserData>(),
	  Callback_Impl_Instance<InstanceClass>(), _func(function)
{
  if (function == 0)
    throw std::exception();
}

template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::
	Callback_Impl_Method_UserData(
	InstanceClass *instance, void (InstanceClass::*function)(UserData&))
	: Callback_Impl(),
	  Callback_Impl_UserData<UserData>(),
	  Callback_Impl_Instance<InstanceClass>(instance), _func(function)
{
  if (function == 0)
    throw std::exception();
}

template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::
	Callback_Impl_Method_UserData(
	InstanceClass *instance, void (InstanceClass::*function)(UserData&),
	UserData *data)
	: Callback_Impl(),
	  Callback_Impl_UserData<UserData>(data),
	  Callback_Impl_Instance<InstanceClass>(instance), _func(function)
{
  if (function == 0)
    throw std::exception();
}

template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::~Callback_Impl_Method_UserData()
{
}

template <class InstanceClass, typename UserData>
void		Callback_Impl_Method_UserData<InstanceClass, UserData>::call(void)
{
  if (this->_data && this->_instance)
    (this->_instance->*_func)(*(this->_data));
  else
    throw std::exception();
}
