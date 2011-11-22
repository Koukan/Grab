#pragma once

#include <string>
#include <map>
#include "bulletmlparser.h"

typedef std::map<std::string, BulletMLParser*>	bulletParsers;

class BulletResourceManager
{
  public:
    BulletResourceManager();
    virtual ~BulletResourceManager();
	bool			addBulletParser(std::string const &path, std::string const &name);

	//getter
	BulletMLParser	*getBulletParser(std::string const &name);

  private:
	bulletParsers	_parsers;
};
