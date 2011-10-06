template <typename UserData1, typename UserData2>
Callback_Impl_UserData2<UserData1, UserData2>::Callback_Impl_UserData2()
	: _data1(0), _data2(0)
{
}

template <typename UserData1, typename UserData2>
Callback_Impl_UserData2<UserData1, UserData2>::Callback_Impl_UserData2
	(UserData1 *data1, UserData2 *data2)
	: _data1(data1), _data2(data2)
{
}

template <typename UserData1, typename UserData2>
Callback_Impl_UserData2<UserData1, UserData2>::~Callback_Impl_UserData2()
{
  if (_data1)
    delete _data1;
  if (_data2)
    delete _data2;
}

template <typename UserData1, typename UserData2>
void	Callback_Impl_UserData2<UserData1, UserData2>::
		setData(UserData1 *data1, UserData2 *data2)
{
  _mem1 = _data1;
  _data1 = data1;
  _mem2 = _data2;
  _data2 = data2;
}

template <typename UserData1, typename UserData2>
void	Callback_Impl_UserData2<UserData1, UserData2>::clearData()
{
  _data1 = _mem1;
  _data2 = _mem2;
}
