template <class InstanceClass>
Callback_Impl_Instance<InstanceClass>::Callback_Impl_Instance(
	InstanceClass *instance)
	: _instance(instance), _mem(0)
{
}

template <class InstanceClass>
Callback_Impl_Instance<InstanceClass>::~Callback_Impl_Instance()
{
}

template <class InstanceClass>
void		Callback_Impl_Instance<InstanceClass>::clearInstance(void)
{
  _instance = _mem;
}

template <class InstanceClass>
void		Callback_Impl_Instance<InstanceClass>::setInstance(InstanceClass *instance)
{
  _mem = _instance;
  _instance = instance;
}
