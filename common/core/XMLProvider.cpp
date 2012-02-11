#include "XMLProvider.hpp"

XMLProvider::XMLProvider(std::string const &handledTag)
  : _id(1), _handledTag(handledTag)
{
}

Resource		*XMLProvider::getResource(std::string const &) const
{
	return 0;
}

void			XMLProvider::deleteResource(std::string const &)
{
}

bool			XMLProvider::setId(uint32_t id)
{
	if (this->_id < id)
	{
		this->_id = id;
		return true;
	}
	return false;
}

std::string const &	XMLProvider::getHandledTag() const
{
  return (this->_handledTag);
}
