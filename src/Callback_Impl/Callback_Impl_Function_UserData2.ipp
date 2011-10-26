template <typename UserData1, typename UserData2>
Callback_Impl_Function_UserData2<UserData1, UserData2>::
Callback_Impl_Function_UserData2(
	void (*function)(UserData1&, UserData2&))
	: Callback_Impl_UserData2<UserData1, UserData2>(), _func(function)
{
}

template <typename UserData1, typename UserData2>
Callback_Impl_Function_UserData2<UserData1, UserData2>::
Callback_Impl_Function_UserData2(
	void (*function)(UserData1&, UserData2&), UserData1 &data1, UserData2 &data2)
	: Callback_Impl_UserData2<UserData1, UserData2>(data1, data2), _func(function)
{
}

template <typename UserData1, typename UserData2>
Callback_Impl_Function_UserData2<UserData1, UserData2>::
~Callback_Impl_Function_UserData2()
{
}

template <typename UserData1, typename UserData2>
void		Callback_Impl_Function_UserData2<UserData1, UserData2>::call()
{
  #if defined(DEBUG)
  if (!this->_data1 || !this->_data2)
    throw std::exception();
  #endif
  (*_func)(*(this->_data1), *(this->_data2));
}
