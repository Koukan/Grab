#ifndef		_CALLBACK_IMPL_
#define 	_CALLBACK_IMPL_

#include <stdexcept>
#include <iostream>

class Callback_Impl
{
  public:
    virtual ~Callback_Impl(){}
    virtual void	call(void) = 0;

  protected:
    Callback_Impl(){}
};

#endif		/* _CALLBACK_IMPL_ */
