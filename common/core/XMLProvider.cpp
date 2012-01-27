#include "XMLProvider.hpp"

XMLProvider::XMLProvider(std::string const &handledTag)
  : _handledTag(handledTag)
{
}

std::string const &	XMLProvider::getHandledTag()
{
  return (this->_handledTag);
}
