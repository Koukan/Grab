template <typename UserData>
Callback_Impl_UserData<UserData>::Callback_Impl_UserData()
	: _data1(0)
{
}

template <typename UserData>
Callback_Impl_UserData<UserData>::Callback_Impl_UserData(UserData &data)
	: _data1(&data)
{
}

template <typename UserData>
Callback_Impl_UserData<UserData>::~Callback_Impl_UserData()
{
  if (_data1)
    delete _data1;
}

template <typename UserData>
void		Callback_Impl_UserData<UserData>::setData(UserData &data)
{
  _data1 = &data;
}
