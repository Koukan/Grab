#pragma once

#include "XMLProvider.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ LoadXMLProvider : public XMLProvider
{
  public:
    LoadXMLProvider();
    virtual ~LoadXMLProvider();
	virtual void		handleXML(TiXmlNode *, ResourceManager &);
};

CORE_END_NAMESPACE
