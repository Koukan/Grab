#ifndef _SINGLETON_
#define _SINGLETON_

#include "NonCopyable.hpp"

template <typename T>
class Singleton : private NonCopyable
{
    public:
        static T        *getInstance()
        {
            if (_singleton == 0)
              _singleton = new T;
            return (static_cast<T*>(_singleton));
        }

        static T        &get()
        {
            if (_singleton == 0)
              _singleton = new T;
            return *(static_cast<T*>(_singleton));
        }

        static void     kill()
        {
            if (_singleton != 0)
			{
                delete _singleton;
                _singleton = 0;
            }
        }

    protected:
	Singleton(){}
	virtual ~Singleton(){}

    private:
        static T    	*_singleton;
};

template <typename T> T		*Singleton<T>::_singleton = 0;

#endif /* _SINGLETON_ */
