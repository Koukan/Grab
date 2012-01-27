template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::Callback_Impl_Method_UserData(
	void (InstanceClass::*function)(UserData&))
	: Callback_Impl_UserData2<UserData, InstanceClass>(), _func(function)
{
  #if defined(DEBUG)
  if (function == 0)
    throw std::exception();
  #endif
}

template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::
	Callback_Impl_Method_UserData(
	InstanceClass &instance, void (InstanceClass::*function)(UserData&))
	: Callback_Impl_UserData2<UserData, InstanceClass>(), _func(function)
{
  this->_data2 = &instance;
  #if defined(DEBUG)
  if (function == 0)
    throw std::exception();
  #endif
}

template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::
	Callback_Impl_Method_UserData(
	InstanceClass &instance, void (InstanceClass::*function)(UserData&),
	UserData &data)
	: Callback_Impl_UserData2<UserData, InstanceClass>(data, instance), _func(function)
{
  #if defined(DEBUG)
  if (function == 0)
    throw std::exception();
  #endif
}

template <class InstanceClass, typename UserData>
Callback_Impl_Method_UserData<InstanceClass, UserData>::~Callback_Impl_Method_UserData()
{
}

template <class InstanceClass, typename UserData>
void		Callback_Impl_Method_UserData<InstanceClass, UserData>::call(void)
{
  #if defined(DEBUG)
  if (!this->_data1 || !this->_data2)
    throw std::exception();
  #endif
  (this->_data2->*_func)(*(this->_data1));
}
