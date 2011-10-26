template <typename UserData>
Callback_Impl_Function_UserData<UserData>::Callback_Impl_Function_UserData(
	void (*function)(UserData&))
	: Callback_Impl_UserData<UserData>(), _func(function)
{
}

template <typename UserData>
Callback_Impl_Function_UserData<UserData>::Callback_Impl_Function_UserData(
	void (*function)(UserData&), UserData &data)
	: Callback_Impl_UserData<UserData>(data), _func(function)
{
}

template <typename UserData>
Callback_Impl_Function_UserData<UserData>::~Callback_Impl_Function_UserData()
{
}

template <typename UserData>
void		Callback_Impl_Function_UserData<UserData>::call()
{
  #if defined(DEBUG)
  if (!this->_data1)
    throw std::exception();
  #endif
  (*_func)(*(this->_data1));
}
