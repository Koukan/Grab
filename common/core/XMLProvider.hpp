#pragma once

#include <string>
#include "tinyxml.h"

class XMLProvider
{
public:
  XMLProvider(std::string const &handledTag);
  virtual ~XMLProvider(){}
  virtual void handleXML(TiXmlNode *) = 0;

  std::string const & getHandledTag();

private:
  std::string _handledTag;
};
