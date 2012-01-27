#pragma once

#include <string>
#include <map>
#include "bulletmlparser.h"

class BulletResourceManager
{
  public:
    BulletResourceManager();
    virtual ~BulletResourceManager();
	bool			addBulletParser(std::string const &path, std::string const &name);

	//getter
	BulletMLParser	*getBulletParser(std::string const &name);

  private:
	typedef std::map<std::string, BulletMLParser*>	bulletParsers;

	bulletParsers	_parsers;
};
