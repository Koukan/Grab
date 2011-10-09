template <class InstanceClass>
Callback_Impl_Method<InstanceClass>::Callback_Impl_Method(
	void (InstanceClass::*function)())
	: Callback_Impl_Instance<InstanceClass>(), _func(function)
{
}

template <class InstanceClass>
Callback_Impl_Method<InstanceClass>::Callback_Impl_Method(
	InstanceClass *instance, void (InstanceClass::*function)())
	: Callback_Impl_Instance<InstanceClass>(instance), _func(function)
{
}

template <class InstanceClass>
Callback_Impl_Method<InstanceClass>::~Callback_Impl_Method()
{
}

template <class InstanceClass>
void		Callback_Impl_Method<InstanceClass>::call()
{
  if (this->_instance)
    (this->_instance->*_func)();
}
