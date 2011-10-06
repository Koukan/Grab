template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::
	Callback_Impl_Method_UserData(
	InstanceClass *instance, void (InstanceClass::*function)(UserData&))
	: Callback_Impl_UserData<UserData>(), _instance(instance), _func(function)
{
  if (instance == 0 || function == 0)
    throw std::exception();
}

template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::
	Callback_Impl_Method_UserData(
	InstanceClass *instance, void (InstanceClass::*function)(UserData&),
	UserData *data)
	: Callback_Impl_UserData<UserData>(data), _instance(instance), _func(function)
{
  if (instance == 0 || function == 0)
    throw std::exception();
}

template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::~Callback_Impl_Method_UserData()
{
}

template <class InstanceClass, typename UserData>
void		Callback_Impl_Method_UserData<InstanceClass, UserData>::call(void)
{
  if (this->_data)
    (_instance->*_func)(*(this->_data));
  else
    throw std::exception();
}
