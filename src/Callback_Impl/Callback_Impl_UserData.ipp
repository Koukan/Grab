template <typename UserData>
Callback_Impl_UserData<UserData>::Callback_Impl_UserData()
	: _data(0)
{
}

template <typename UserData>
Callback_Impl_UserData<UserData>::Callback_Impl_UserData(UserData &data)
	: _data(&data)
{
}

template <typename UserData>
Callback_Impl_UserData<UserData>::~Callback_Impl_UserData()
{
  if (_data)
    delete _data;
}

template <typename UserData>
void		Callback_Impl_UserData<UserData>::setData(UserData &data)
{
  _mem = _data;
  _data = &data;
}

template <typename UserData>
void		Callback_Impl_UserData<UserData>::clearData()
{
  _data = _mem;
}
