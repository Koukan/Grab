#ifndef		_CALLBACK_IMPL_
#define 	_CALLBACK_IMPL_

#include <stdexcept>

class Callback_Impl
{
  public:
    virtual ~Callback_Impl(){}
    virtual void	call(void)
    {
      throw std::exception();
    }

  protected:
    Callback_Impl(){}
};

#endif		/* _CALLBACK_IMPL_ */
