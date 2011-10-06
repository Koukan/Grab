template <class InstanceClass, typename UserData1, typename UserData2>
Callback_Impl_Method_UserData2<InstanceClass, UserData1, UserData2>::
Callback_Impl_Method_UserData2(InstanceClass *instance,
	void (InstanceClass::*function)(UserData1&, UserData2&))
	: Callback_Impl_UserData2<UserData1, UserData2>(), _instance(instance), _func(function)
{
  if (instance == 0 || function == 0)
    throw std::exception();
}

template <class InstanceClass, typename UserData1, typename UserData2>
Callback_Impl_Method_UserData2<InstanceClass, UserData1, UserData2>::
Callback_Impl_Method_UserData2( InstanceClass *instance,
	void (InstanceClass::*function)(UserData1&, UserData2&),
	UserData1 *data1, UserData2 *data2)
	: Callback_Impl_UserData2<UserData1, UserData2>(data1, data2),
		_instance(instance), _func(function)
{
  if (instance == 0 || function == 0)
    throw std::exception();
}

template <class InstanceClass, typename UserData1, typename UserData2>
Callback_Impl_Method_UserData2<InstanceClass, UserData1, UserData2>::
~Callback_Impl_Method_UserData2()
{
}

template <class InstanceClass, typename UserData1, typename UserData2>
void		Callback_Impl_Method_UserData2<InstanceClass, UserData1, UserData2>::call(void)
{
  if (this->_data1 && this->_data2)
    (_instance->*_func)(*(this->_data1), *(this->_data2));
  else
    throw std::exception();
}
