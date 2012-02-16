#pragma once

#include <string>
#include <map>
#include "bulletmlparser.h"
#include "XMLProvider.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ BulletResourceManager : public XMLProvider
{
  public:
    BulletResourceManager();
    virtual ~BulletResourceManager();
	void				handleXML(TiXmlNode*, ResourceManager&);
	BulletMLParser		*addBulletParser(std::string const &path, std::string const &name, ResourceManager &);
};

CORE_END_NAMESPACE
