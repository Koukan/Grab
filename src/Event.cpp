#include "Event.hpp"

Event::Event(const std::string &type) : _type(type)
{
}

Event::~Event()
{
}

void			Event::setType(const std::string &type)
{
  if (!type.empty())
    _type = type;
}

const std::string	&Event::getType(void) const
{
  return _type;
}
