template <typename UserData1, typename UserData2>
Callback_Impl_UserData2<UserData1, UserData2>::Callback_Impl_UserData2()
	: Callback_Impl_UserData<UserData1>() , _data2(0)
{
}

template <typename UserData1, typename UserData2>
Callback_Impl_UserData2<UserData1, UserData2>::Callback_Impl_UserData2
	(UserData1 &data1)
	: Callback_Impl_UserData<UserData1>(data1), _data2(0)
{
}

template <typename UserData1, typename UserData2>
Callback_Impl_UserData2<UserData1, UserData2>::Callback_Impl_UserData2
	(UserData1 &data1, UserData2 &data2)
	: Callback_Impl_UserData<UserData1>(data1), _data2(&data2)
{
}

template <typename UserData1, typename UserData2>
Callback_Impl_UserData2<UserData1, UserData2>::~Callback_Impl_UserData2()
{
  if (this->_data2)
    delete this->_data2;
}

template <typename UserData1, typename UserData2>
void	Callback_Impl_UserData2<UserData1, UserData2>::
		setData(UserData1 &data1, UserData2 &data2)
{
  this->_data1 = &data1;
  this->_data2 = &data2;
}
