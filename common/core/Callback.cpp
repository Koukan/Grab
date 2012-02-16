#include "Callback.hpp"
#include "Callback_Impl_Function.hpp"

CORE_USE_NAMESPACE

Callback::Callback(void(*function)())
{
  _callback = new Callback_Impl_Function(function);
}

Callback::~Callback()
{
  delete _callback;
}

void		Callback::call()
{
  _callback->call();
}

void		Callback::operator ()()
{
  this->call();
}
