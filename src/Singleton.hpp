#ifndef _SINGLETON_
#define _SINGLETON_

#include "NonCopyable.hpp"

template <typename T>
class Singleton : private NonCopyable
{
    public:
        static T        *getInstance()
        {
            if (_singleton == NULL)
              _singleton = new T;
            return (static_cast<T*>(_singleton));
        }

        static T        &get()
        {
            if (_singleton == NULL)
              _singleton = new T;
            return *(static_cast<T*>(_singleton));
        }

        static void     kill()
        {
            if (_singleton != NULL)
            {
                delete _singleton;
                _singleton = NULL;
            }
        }

    protected:
	Singleton(){}
	virtual ~Singleton(){}

    private:
        static T    	*_singleton;
};

template <typename T> T		*Singleton<T>::_singleton = NULL;

#endif /* _SINGLETON_ */
