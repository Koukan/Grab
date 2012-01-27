#include "Callback.hpp"
#include "Callback_Impl_Function.hpp"

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
