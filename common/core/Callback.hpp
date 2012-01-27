#ifndef		_CALLBACK_
#define 	_CALLBACK_

#include "Callback_Impl.hpp"
#include "Callback_Impl_Function.hpp"
#include "Callback_Impl_Method.hpp"
#include "Callback_Impl_Function_UserData.hpp"
#include "Callback_Impl_Method_UserData.hpp"
#include "Callback_Impl_Function_UserData2.hpp"

class Callback
{
  public:
    // 0 argurment
    Callback(void(*function)());
    template <class InstanceClass>
    Callback(void(InstanceClass::*function)());
    template <class InstanceClass>
    Callback(InstanceClass &instance, void(InstanceClass::*function)());
    // 1 argument
    template <typename UserData>
    Callback(void(*function)(UserData&));
    template <typename UserData>
    Callback(void(*function)(UserData&), UserData &data);
    template <class InstanceClass, typename UserData>
    Callback(void(InstanceClass::*function)(UserData&));
    template <class InstanceClass, typename UserData>
    Callback(InstanceClass &instance, void(InstanceClass::*function)(UserData&));
    template <class InstanceClass, typename UserData>
    Callback(InstanceClass &instance, void(InstanceClass::*function)(UserData&),
	     UserData &data);
    // 2 arguments
    template <typename UserData1, typename UserData2>
    Callback(void(*function)(UserData1&, UserData2&));
    template <typename UserData1, typename UserData2>
    Callback(void(*function)(UserData1&, UserData2&),
	     UserData1 &data1, UserData2 &data2);
    // end constructor

    virtual ~Callback();
    void		call();
    template <typename UserData /* or Instance */>
    void		call(UserData &data);
    template <typename UserData1 /* or Instance */, typename UserData2>
    void		call(UserData1 &data1, UserData2 &data2);

    void		operator()();
    template <typename UserData /* or Instance */>
    void		operator()(UserData &data);
    template <typename UserData1 /* or Instance */, typename UserData2>
    void		operator()(UserData1 &data1, UserData2 &data2);

  protected:
    Callback();

  private:
    Callback_Impl	*_callback;
    bool		_instance;
};

#include "Callback.ipp"

#endif		/* _CALLBACK_ */
