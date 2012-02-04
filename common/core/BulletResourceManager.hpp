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
	BulletMLParser		*addBulletParser(std::string const &path, std::string const &name);

	//getter
	virtual Resource	*getResource(std::string const &name) const;

	virtual void		deleteResource(std::string const &name);

  private:
	typedef std::map<std::string, BulletMLParser*>	bulletParsers;

	bulletParsers	_parsers;
};
