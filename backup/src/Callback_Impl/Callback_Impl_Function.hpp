#ifndef		_CALLBACK_IMPL_FUNCTION_
#define 	_CALLBACK_IMPL_FUNCTION_

#include "Callback_Impl.hpp"

class Callback_Impl_Function : public Callback_Impl
{
  public:
    Callback_Impl_Function(void (*function)());
    virtual ~Callback_Impl_Function();
    virtual void	call();

  private:
    void		(*_func)();
};

#endif		/* _CALLBACK_IMPL_FUNCTION_ */
