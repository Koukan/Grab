template <class InstanceClass>
Callback_Impl_Method<InstanceClass>::Callback_Impl_Method(
	void (InstanceClass::*function)())
	: Callback_Impl_UserData<InstanceClass>(), _func(function)
{
}

template <class InstanceClass>
Callback_Impl_Method<InstanceClass>::Callback_Impl_Method(
	InstanceClass &instance, void (InstanceClass::*function)())
	: Callback_Impl_UserData<InstanceClass>(instance), _func(function)
{
}

template <class InstanceClass>
Callback_Impl_Method<InstanceClass>::~Callback_Impl_Method()
{
}

template <class InstanceClass>
void		Callback_Impl_Method<InstanceClass>::call()
{
  #if defined(DEBUG)
  if (!this->_data1)
    throw std::exception();
  #endif
  (this->_data1->*_func)();
}
