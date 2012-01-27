#ifndef		_ITHREADSUBSCRIBER_
# define	_ITHREADSUBSCRIBER_

class		IThreadSubscriber
{
public:
  virtual ~IThreadSubscriber(){}
  virtual void call() = 0;
};

#endif		/* !_ITRHEADSUBSCRIBER_*/
