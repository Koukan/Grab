#ifndef _NONCOPYABLE_
#define _NONCOPYABLE_

class NonCopyable
{
protected:
      NonCopyable(){}
      virtual ~NonCopyable(){}

private:
      NonCopyable(const NonCopyable &other);
      NonCopyable &operator=(const NonCopyable &other);
};


#endif /* _NONCOPYABLE_ */
