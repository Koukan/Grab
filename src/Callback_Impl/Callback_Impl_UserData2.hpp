#ifndef		_CALLBACK_IMPL_USERDATA2_
#define 	_CALLBACK_IMPL_USERDATA2_

#include "Callback_Impl.hpp"

template <typename UserData1, typename UserData2>
class Callback_Impl_UserData2 : public Callback_Impl
{
  public:
    Callback_Impl_UserData2(UserData1 *data1, UserData2 *data2);
    virtual ~Callback_Impl_UserData2();
    void		setData(UserData1 *data1, UserData2 *data2);
    void		clearData();

  protected:
    Callback_Impl_UserData2();

    UserData1		*_data1;
    UserData2		*_data2;
    UserData1		*_mem1;
    UserData2		*_mem2;
};

#include "Callback_Impl_UserData2.ipp"

#endif		/* _CALLBACK_IMPL_USERDATA2_ */
