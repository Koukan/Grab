#include "Callback_Impl_Function.hpp"

Callback_Impl_Function::Callback_Impl_Function(void (*function)())
	: _func(function)
{
}

Callback_Impl_Function::~Callback_Impl_Function()
{
}

void		Callback_Impl_Function::call()
{
  (*_func)();
}
