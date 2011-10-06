template <class InstanceClass>
Callback_Impl_Method<InstanceClass>::Callback_Impl_Method(
		InstanceClass *instance, void (InstanceClass::*function)())
	: _instance(instance), _func(function)
{
}

template <class InstanceClass>
Callback_Impl_Method<InstanceClass>::~Callback_Impl_Method()
{
}

template <class InstanceClass>
void		Callback_Impl_Method<InstanceClass>::call()
{
  (_instance->*_func)();
}
