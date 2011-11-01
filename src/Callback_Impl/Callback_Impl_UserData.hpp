#ifndef		_CALLBACK_IMPL_USERDATA_
#define 	_CALLBACK_IMPL_USERDATA_

template <typename UserData>
class Callback_Impl_UserData
{
  public:
    virtual ~Callback_Impl_UserData();
    void	setData(UserData &data);

  protected:
    Callback_Impl_UserData();
    Callback_Impl_UserData(UserData &data);

    UserData		*_data1;
};

#include "Callback_Impl_UserData.ipp"

#endif		/* _CALLBACK_IMPL_USERDATA_ */
