#include <iostream>
#include "BulletResourceManager.hpp"
#include "bulletmlparser-tinyxml.h"
#include "bulletmlerror.h"

CORE_USE_NAMESPACE

BulletResourceManager::BulletResourceManager()
	: XMLProvider("bulletml", 3)
{
}

BulletResourceManager::~BulletResourceManager()
{
}

void		BulletResourceManager::handleXML(TiXmlNode *parent, ResourceManager &manager)
{
	std::string		name;
	std::string		parserName;
	std::string		parserPath;

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
		this->addBulletParser(parserPath, parserName, manager);
}

BulletMLParser		*BulletResourceManager::addBulletParser(std::string const &path,
													std::string const &name, ResourceManager &manager)
{
	ResourceMap::iterator	it = this->_resources.find(name);

	if (it != this->_resources.end())
	{
		this->XMLProvider::addResource(name, *it->second, manager);
		return static_cast<BulletMLParser*>(it->second);
	}
	try
	{
		BulletMLParserTinyXML	*parser = new BulletMLParserTinyXML(path);
		parser->build();
		this->XMLProvider::addResource(name, *parser, manager);
		return static_cast<BulletMLParser*>(parser);
	}
	catch (BulletMLError e)
	{
		std::cerr << "BulletML xml \"" << path << "\" don't exist or not valid" << std::endl;
		return 0;
	}
	return 0;
}
