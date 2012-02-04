#pragma once

#include "XMLProvider.hpp"

class LoadXMLProvider : public XMLProvider
{
  public:
    LoadXMLProvider();
    virtual ~LoadXMLProvider();
	virtual void		handleXML(TiXmlNode *, ResourceManager &);
};
