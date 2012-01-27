#include <iostream>
#include <stdexcept>
#include "ResourceManager.hpp"
#include "Sprite.hpp"
#include "Font.hpp"
#include "Converter.hpp"
#include "LoadXMLProvider.hpp"
#include "SpriteProvider.hpp"
#include "FontProvider.hpp"

ResourceManager::ResourceManager()
  : XMLProvider("resources")
{
  this->addProvider(*this);
  this->addProvider(*new LoadXMLProvider(*this));
}

ResourceManager::~ResourceManager()
{
  ProviderMap::iterator it;

  for (it = this->_providers.begin(); it != this->_providers.end(); ++it)
    if ((*it).second != this)
      delete (*it).second;
}

void			ResourceManager::load(std::string const &path)
{
	if (!this->_document.LoadFile(path.c_str()))
		throw std::runtime_error(path + ": not found");
	this->handleXML(&this->_document);
}

void			ResourceManager::addProvider(XMLProvider &provider)
{
  if (this->_providers.find(provider.getHandledTag()) == this->_providers.end())
    this->_providers[provider.getHandledTag()] = &provider;
}

Sprite			*ResourceManager::getSprite(std::string const &name) const
{
  ProviderMap::const_iterator it;

  if ((it = this->_providers.find("sprite")) != this->_providers.end())
    return (static_cast<SpriteProvider*>((*it).second))->getSprite(name);
  return 0;
}

Font			*ResourceManager::getFont(std::string const &name) const
{
  ProviderMap::const_iterator it;

  if ((it = this->_providers.find("font")) != this->_providers.end())
    return (static_cast<FontProvider*>((*it).second))->getFont(name);
  return 0;
}

void			ResourceManager::handleXML(TiXmlNode *parent)
{
	static Method<TiXmlNode::NodeType> const	methods[] = {
			{TiXmlNode::DOCUMENT, &ResourceManager::loadDocument},
			{TiXmlNode::ELEMENT, &ResourceManager::loadElement},
			{TiXmlNode::COMMENT, &ResourceManager::loadComment},
			{TiXmlNode::UNKNOWN, &ResourceManager::loadUnknown},
			{TiXmlNode::TEXT, &ResourceManager::loadText},
			{TiXmlNode::DECLARATION, &ResourceManager::loadDeclaration}
	};
	size_t				i;
	TiXmlNode::NodeType		type;

	if (!parent)
		return ;
	for (TiXmlNode *child = parent->FirstChild(); child != 0;
		 child = child->NextSibling())
	{
		type = static_cast<TiXmlNode::NodeType>(child->Type());
		for (i = 0; i != (sizeof(methods) / sizeof(*methods)); i++)
		{
			if (type == methods[i].name)
			{
				(this->*methods[i].func)(child);
				break ;
			}
		}
	}
}

void			ResourceManager::loadDocument(TiXmlNode *parent)
{
  this->handleXML(parent);
}

void			ResourceManager::loadElement(TiXmlNode *parent)
{
	std::string		name;
	ProviderMap::iterator	it;

	for (TiXmlNode *child = parent->FirstChild(); child != 0;
		 child = child->NextSibling())
	{
		name = child->Value();
		for (it = this->_providers.begin(); it != this->_providers.end(); ++it)
		{
		  if (name == (*it).first)
		    {
		      (*it).second->handleXML(child);
		      break ;
		    }
		}
	}
}

void			ResourceManager::loadComment(TiXmlNode *)
{
}

void			ResourceManager::loadUnknown(TiXmlNode *)
{
}

void			ResourceManager::loadText(TiXmlNode *)
{
}

void			ResourceManager::loadDeclaration(TiXmlNode *)
{
}

void		ResourceManager::get2Int(std::string const &data,
					 std::string const &sep,
					 int &a, int &b)
{
	size_t	pos = data.find(sep);

	a = Converter::toInt<int>(data);
	if (pos == std::string::npos)
		b = 0;
	else
		b = Converter::toInt<int>(data.substr(pos + sep.size()));
}
