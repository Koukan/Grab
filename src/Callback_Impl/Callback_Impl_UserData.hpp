#ifndef		_CALLBACK_IMPL_USERDATA_
#define 	_CALLBACK_IMPL_USERDATA_

#include "Callback_Impl.hpp"

template <typename UserData>
class Callback_Impl_UserData
{
  public:
    Callback_Impl_UserData(UserData *data);
    virtual ~Callback_Impl_UserData();
    void		setData(UserData *data);
    void		clearData();

  protected:
    Callback_Impl_UserData();

    UserData		*_data;
    UserData		*_mem;
};

#include "Callback_Impl_UserData.ipp"

#endif		/* _CALLBACK_IMPL_USERDATA_ */
