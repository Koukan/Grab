#ifndef		_ThreadSubscriber_
# define	_ThreadSubscriber_

#include "IThreadSubscriber.hpp"

template <typename T>
class		ThreadMemberFunc : public IThreadSubscriber
{
public:
  ThreadMemberFunc(T *obj, void (T::*func)()) : _obj(obj), _func(func)
  {}

  virtual ~ThreadMemberFunc(){};
  virtual void	call()
  {
    (_obj->*_func)();
  }

private:
  T		*_obj;
  void		(T::*_func)();
};


template <typename T>
class		ThreadFunctor : public IThreadSubscriber
{
public:

  ThreadFunctor(T &obj) : _call(obj)
  {}

  virtual ~ThreadFunctor(){};
  virtual void	call()
  {
    _call();
  }

private:
  T		&_call;
};

template <typename T, typename Arg>
class		ThreadFunctorArg : public IThreadSubscriber
{
public:

  ThreadFunctorArg(T &obj, Arg arg) : _call(obj), _arg(arg)
  {}

  virtual ~ThreadFunctorArg(){};
  virtual void	call()
  {
    _call(_arg);
  }

private:
  T		&_call;
  Arg		_arg;
};

#endif		/* !_ThreadSubscriber_*/
