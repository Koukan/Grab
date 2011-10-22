#ifndef		_CALLBACK_IPP_
#define 	_CALLBACK_IPP_

template <typename UserData>
Callback::Callback(void(*function)(UserData&))
	: _callback(new Callback_Impl_Function_UserData<UserData>(function))
{
}

template <typename UserData>
Callback::Callback(void(*function)(UserData&), UserData *data)
	: _callback(new Callback_Impl_Function_UserData<UserData>(function, data))
{
}

template <class InstanceClass>
Callback::Callback(void(InstanceClass::*function)())
	: _callback(new Callback_Impl_Method<InstanceClass>(function))
{
}

template <class InstanceClass>
Callback::Callback(InstanceClass *instance, void(InstanceClass::*function)())
	: _callback(new Callback_Impl_Method<InstanceClass>(instance, function))
{
}

template <class InstanceClass, typename UserData>
Callback::Callback(void(InstanceClass::*function)(UserData&))
	: _callback(new Callback_Impl_Method_UserData<InstanceClass, UserData>
		(function))
{
}

template <class InstanceClass, typename UserData>
Callback::Callback(InstanceClass *instance, void(InstanceClass::*function)(UserData&))
	: _callback(new Callback_Impl_Method_UserData<InstanceClass, UserData>
		(instance, function))
{
}

template <class InstanceClass, typename UserData>
Callback::Callback(InstanceClass *instance, void(InstanceClass::*function)(UserData&),
		   UserData *data)
	: _callback(new Callback_Impl_Method_UserData<InstanceClass, UserData>
		(instance, function, data))
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
		   UserData1 *data1, UserData2 *data2)
	: _callback(new Callback_Impl_Function_UserData2<UserData1, UserData2>
		(function, data1, data2))
{
}

template <class InstanceClass, typename UserData1, typename UserData2>
Callback::Callback(InstanceClass *instance,
		   void(InstanceClass::*function)(UserData1&, UserData2&))
	: _callback(new Callback_Impl_Method_UserData2<InstanceClass, UserData1, UserData2>
		(instance, function))
{
}

template <class InstanceClass, typename UserData1, typename UserData2>
Callback::Callback(InstanceClass *instance,
		   void (InstanceClass::*function)(UserData1&, UserData2&),
		   UserData1 *data1, UserData2 *data2)
	: _callback(new Callback_Impl_Method_UserData2<InstanceClass, UserData1, UserData2>
		(instance, function, data1, data2))
{
}

template <typename InstanceClass>
void		Callback::callInstance(InstanceClass *instance)
{
  #if defined (DEBUG)
  if (!dynamic_cast<Callback_Impl_Instance<InstanceClass>*>(_callback))
    throw std::exception();
  #endif
  Callback_Impl_Instance<InstanceClass>	*callback =
  reinterpret_cast<Callback_Impl_Instance<InstanceClass>*>(_callback);

  callback->setInstance(instance);
  _callback->call();
  callback->clearInstance();
}

template <typename UserData>
void		Callback::call(UserData *data)
{
  #if defined (DEBUG)
  if (!dynamic_cast<Callback_Impl_UserData<UserData>*>(_callback))
    throw std::exception();
  #endif
  Callback_Impl_UserData<UserData>	*callback =
  reinterpret_cast<Callback_Impl_UserData<UserData>*>(_callback);

  callback->setData(data);
  _callback->call();
  callback->clearData();
}

template <typename InstanceClass, typename UserData>
#include <iostream>
void		Callback::callInstance(InstanceClass *instance, UserData *data)
{
  #if defined (DEBUG)
  if (!dynamic_cast<Callback_Impl_Method_UserData<InstanceClass, UserData>*>(_callback))
    throw std::exception();
  #endif
  Callback_Impl_Method_UserData<InstanceClass, UserData>	*callback =
  reinterpret_cast<Callback_Impl_Method_UserData<InstanceClass, UserData>*>(_callback);

  callback->setData(data);
  callback->setInstance(instance);
  _callback->call();
  callback->clearData();
  callback->clearInstance();
}

template <typename UserData1, typename UserData2>
void		Callback::call(UserData1 *data1, UserData2 *data2)
{
  #if defined (DEBUG)
  if (!dynamic_cast<Callback_Impl_UserData2<UserData1, UserData2>*>(_callback))
    throw std::exception();
  #endif
  Callback_Impl_UserData2<UserData1, UserData2>	*callback =
  reinterpret_cast<Callback_Impl_UserData2<UserData1, UserData2>*>(_callback);

  callback->setData(data1, data2);
  _callback->call();
  callback->clearData();
}

#endif		/* _CALLBACK_IPP_ */
