#ifndef		_EVENT_
#define 	_EVENT_

#include <string>

class Event
{
  public:
    Event(const std::string &type);
    virtual ~Event();

    //setter
    void		setType(const std::string &type);

    //getter
    const std::string	&getType() const;

  private:
    Event();

    std::string		_type;
};

#endif		/* _EVENT_ */
