#include <iostream>
#include "BulletResourceManager.hpp"
#include "bulletmlparser-tinyxml.h"
#include "bulletmlerror.h"

BulletResourceManager::BulletResourceManager()
	: XMLProvider("bulletml")
{
}

BulletResourceManager::~BulletResourceManager()
{
	for (bulletParsers::iterator it = _parsers.begin();
		 it != _parsers.end(); it++)
		delete it->second;
}

void		BulletResourceManager::handleXML(TiXmlNode *parent, ResourceManager &manager)
{
	std::string		name;
	std::string		parserName;
	std::string		parserPath;
	BulletMLParser	*parser = 0;

	for (TiXmlAttribute *attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
		attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "name")
			parserName = attrib->Value();
		else if (name == "file")
			parserPath = attrib->Value();
	}
	if (!parserPath.empty() && !parserName.empty())
	{
		parser = addBulletParser(parserPath, parserName);
		if (parser)
			manager.addBulletParser(*parser);
	}
}

BulletMLParser		*BulletResourceManager::addBulletParser(std::string const &path,
													std::string const &name)
{
	bulletParsers::iterator	it = _parsers.find(name);

	if (it != _parsers.end())
		return it->second;
	try
	{
		BulletMLParserTinyXML	*parser = new BulletMLParserTinyXML(path);
		parser->build();
		parser->setResourceId(this->_id++);
		parser->setResourceName(name);
		parser->setResourceType(3);
		parser->setResourceProvider(this);
		_parsers[name] = parser;
		return parser;
	}
	catch (BulletMLError e)
	{
		std::cerr << "BulletML xml \"" << path << "\" don't exist or not valid" << std::endl;
		return 0;
	}
	return 0;
}

Resource		*BulletResourceManager::getResource(std::string const &name) const
{
	bulletParsers::const_iterator	it = _parsers.find(name);

	if (it != _parsers.end())
		return it->second;
	BulletMLError::doAssert("The parser " + name + " don't exist");
	return 0;
}

void			BulletResourceManager::deleteResource(std::string const &name)
{
	this->_parsers.erase(name);
}
