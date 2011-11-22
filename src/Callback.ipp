#ifndef		_CALLBACK_IPP_
#define 	_CALLBACK_IPP_

template <typename UserData>
Callback::Callback(void(*function)(UserData&))
	: _callback(new Callback_Impl_Function_UserData<UserData>(function)),
	  _instance(false)
{
}

template <typename UserData>
Callback::Callback(void(*function)(UserData&), UserData &data)
	: _callback(new Callback_Impl_Function_UserData<UserData>(function, data)),
	  _instance(false)
{
}

template <class InstanceClass>
Callback::Callback(void(InstanceClass::*function)())
	: _callback(new Callback_Impl_Method<InstanceClass>(function)),
	  _instance(true)
{
}

template <class InstanceClass>
Callback::Callback(InstanceClass &instance, void(InstanceClass::*function)())
	: _callback(new Callback_Impl_Method<InstanceClass>(instance, function)),
	  _instance(true)
{
}

template <class InstanceClass, typename UserData>
Callback::Callback(void(InstanceClass::*function)(UserData&))
	: _callback(new Callback_Impl_Method_UserData<InstanceClass, UserData>
		(function)), _instance(true)
{
}

template <class InstanceClass, typename UserData>
Callback::Callback(InstanceClass &instance, void(InstanceClass::*function)(UserData&))
	: _callback(new Callback_Impl_Method_UserData<InstanceClass, UserData>
		(instance, function)), _instance(true)
{
}

template <class InstanceClass, typename UserData>
Callback::Callback(InstanceClass &instance, void(InstanceClass::*function)(UserData&),
		   UserData &data)
	: _callback(new Callback_Impl_Method_UserData<InstanceClass, UserData>
		(instance, function, data)), _instance(true)
{
}

template <typename UserData1, typename UserData2>
Callback::Callback(void(*function)(UserData1&, UserData2&))
	: _callback(new Callback_Impl_Function_UserData2<UserData1, UserData2>
		(function))
{
}

template <typename UserData1, typename UserData2>
Callback::Callback(void(*function)(UserData1&, UserData2&),
		   UserData1 &data1, UserData2 &data2)
	: _callback(new Callback_Impl_Function_UserData2<UserData1, UserData2>
		(function, data1, data2))
{
}


template <typename UserData>
void		Callback::call(UserData &data)
{ 
  #if defined (DEBUG)
  if (!dynamic_cast<Callback_Impl_UserData<UserData>*>(_callback))
    throw std::exception();
  #endif
  Callback_Impl_UserData<UserData>	*callback =
  dynamic_cast<Callback_Impl_UserData<UserData>*>(_callback);

  if (callback)
  {
    callback->setData(data);
    _callback->call();
  }
}

template <typename UserData1, typename UserData2>
void		Callback::call(UserData1 &data1, UserData2 &data2)
{
  if (_instance)
  {
    Callback_Impl_UserData2<UserData2, UserData1>	*callback =
    dynamic_cast<Callback_Impl_UserData2<UserData2, UserData1>*>(_callback);
    callback->setData(data2, data1);
    _callback->call();
  }
  else
  {
    Callback_Impl_UserData2<UserData1, UserData2>	*callback =
    dynamic_cast<Callback_Impl_UserData2<UserData1, UserData2>*>(_callback);
    if (callback)
    {
      callback->setData(data1, data2);
      _callback->call();
    }
  }
}

template <typename UserData>
void		Callback::operator()(UserData &data)
{
  this->call(data);
}

template <typename UserData1, typename UserData2>
void            Callback::operator()(UserData1 &data1, UserData2 &data2)
{
  this->call(data1, data2);
}

#endif		/* _CALLBACK_IPP_ */
