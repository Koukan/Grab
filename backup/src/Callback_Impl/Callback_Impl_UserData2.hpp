#ifndef		_CALLBACK_IMPL_USERDATA2_
#define 	_CALLBACK_IMPL_USERDATA2_

#include "Callback_Impl_UserData.hpp"

template <typename UserData1, typename UserData2>
class Callback_Impl_UserData2 : public Callback_Impl_UserData<UserData1>
{
  public:
    virtual ~Callback_Impl_UserData2();
    void	setData(UserData1 &data1, UserData2 &data2);

  protected:
    Callback_Impl_UserData2();
    Callback_Impl_UserData2(UserData1 &data1);
    Callback_Impl_UserData2(UserData1 &data1, UserData2 &data2);

    UserData2		*_data2;
};

#include "Callback_Impl_UserData2.ipp"

#endif		/* _CALLBACK_IMPL_USERDATA2_ */
