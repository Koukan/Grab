#ifndef		_CALLBACK_
#define 	_CALLBACK_

#include "Callback_Impl.hpp"
#include "Callback_Impl_Function.hpp"
#include "Callback_Impl_Method.hpp"
#include "Callback_Impl_Function_UserData.hpp"
#include "Callback_Impl_Method_UserData.hpp"
#include "Callback_Impl_Function_UserData2.hpp"
#include "Callback_Impl_Method_UserData2.hpp"

class Callback
{
  public:
    // 0 argurment
    Callback(void(*function)());
    template <class InstanceClass>
    Callback(InstanceClass *instance, void(InstanceClass::*function)());
    // 1 argument
    template <typename UserData>
    Callback(void(*function)(UserData&));
    template <typename UserData>
    Callback(void(*function)(UserData&), UserData *data);
    template <class InstanceClass, typename UserData>
    Callback(InstanceClass *instance, void(InstanceClass::*function)(UserData&));
    template <class InstanceClass, typename UserData>
    Callback(InstanceClass *instance, void(InstanceClass::*function)(UserData&), UserData *data);
    // 2 arguments
    template <typename UserData1, typename UserData2>
    Callback(void(*function)(UserData1&, UserData2&));
    template <typename UserData1, typename UserData2>
    Callback(void(*function)(UserData1&, UserData2&),
	     UserData1 *data1, UserData2 *data2);
    template <class InstanceClass, typename UserData1, typename UserData2>
    Callback(InstanceClass *instance,
	     void(InstanceClass::*function)(UserData1&, UserData2&));
    template <class InstanceClass, typename UserData1, typename UserData2>
    Callback(InstanceClass *instance,
	     void (InstanceClass::*function)(UserData1&, UserData2&),
	     UserData1 *data1, UserData2 *data2);
    virtual ~Callback();
    void		call();
    template <typename UserData>
    void		call(UserData *data);
    template <typename UserData1, typename UserData2>
    void		call(UserData1 *data1, UserData2 *data2);

  protected:
    Callback();

  private:
    Callback_Impl	*_callback;
};

#include "Callback.ipp"

#endif		/* _CALLBACK_ */
