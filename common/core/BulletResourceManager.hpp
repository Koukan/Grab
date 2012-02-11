#pragma once

#include <string>
#include <map>
#include "bulletmlparser.h"
#include "XMLProvider.hpp"

class BulletResourceManager : public XMLProvider
{
  public:
    BulletResourceManager();
    virtual ~BulletResourceManager();
	void				handleXML(TiXmlNode*, ResourceManager&);
	BulletMLParser		*addBulletParser(std::string const &path, std::string const &name, ResourceManager &);
	virtual void		addResource(Resource &, ResourceManager &);
};
