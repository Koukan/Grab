#pragma once

#include "XMLProvider.hpp"

class ResourceManager;

class LoadXMLProvider : public XMLProvider
{
  public:
    LoadXMLProvider(ResourceManager &manager);
    virtual ~LoadXMLProvider();
	virtual void	handleXML(TiXmlNode *node);

  private:
	ResourceManager		&_manager;
};
