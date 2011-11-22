#include <ClanLib/core.h>
#include "BulletResourceManager.hpp"
#include "bulletmlparser-tinyxml.h"
#include "bulletmlerror.h"

BulletResourceManager::BulletResourceManager()
{
}

BulletResourceManager::~BulletResourceManager()
{
	for (bulletParsers::iterator it = _parsers.begin();
		 it != _parsers.end(); it++)
		delete it->second;
}

bool		BulletResourceManager::addBulletParser(std::string const &path,
													std::string const &name)
{
	bulletParsers::iterator	it = _parsers.find(name);
	BulletMLParser 			*mem_parser = 0;

	if (it != _parsers.end())
		mem_parser = it->second;
	try
	{
		BulletMLParserTinyXML *parser = new BulletMLParserTinyXML(path);
		parser->build();
		_parsers[name] = parser;
		if (mem_parser)
			delete mem_parser;

	}
	catch (BulletMLError e)
	{
		cl_log_event("system", "BulletML xml \"" + path + "\" don't exist or not valid");
		return false;
	}
	return true;
}

BulletMLParser		*BulletResourceManager::getBulletParser(std::string const &name)
{
	bulletParsers::const_iterator	it = _parsers.find(name);

	if (it != _parsers.end())
		return it->second;
	BulletMLError::doAssert("The parser " + name + " don't exist");
	return 0;
}
