#include <iostream>
#include <stdexcept>
#include "GlobalResourceManager.hpp"
#include "Sprite.hpp"
#include "Font.hpp"
#include "Converter.hpp"
#include "LoadXMLProvider.hpp"
#include "SpriteProvider.hpp"
#include "FontProvider.hpp"

GlobalResourceManager::GlobalResourceManager()
  : XMLProvider("resources"), _spriteProvider(0), _fontProvider(0)
{
  this->addProvider(*this);
  this->addProvider(this->_bulletProvider);
  this->addProvider(*new LoadXMLProvider());
}

GlobalResourceManager::~GlobalResourceManager()
{
	ProviderMap::iterator it;

	for (it = this->_providers.begin(); it != this->_providers.end(); ++it)
	{
		if ((*it).second != this)
			delete (*it).second;
	}
}

void		GlobalResourceManager::load(std::string const &path, ResourceManager &manager)
{
	if (!this->_document.LoadFile(path.c_str()))
		throw std::runtime_error(path + ": not found");
	this->handleXML(&this->_document, manager);
}

void		GlobalResourceManager::addProvider(XMLProvider &provider)
{
	if (provider.getHandledTag() == "sprite")
	{
		if (!this->_spriteProvider)
			this->_spriteProvider = static_cast<SpriteProvider*>(&provider);
	}
	else if (provider.getHandledTag() == "font")
	{
		if (!this->_fontProvider)
			this->_fontProvider = static_cast<FontProvider*>(&provider);
	}
	if (this->_providers.find(provider.getHandledTag()) == this->_providers.end())
		this->_providers[provider.getHandledTag()] = &provider;
}

void		GlobalResourceManager::addBulletParser(std::string const &path,
										std::string const &name)
{
	this->_bulletProvider.addBulletParser(path, name);

}

XMLProvider	*GlobalResourceManager::getProvider(std::string const &name) const
{
	ProviderMap::const_iterator	it = this->_providers.find(name);

	if (it != this->_providers.end())
		return it->second;
	return 0;
}

Sprite		*GlobalResourceManager::getSprite(std::string const &name) const
{
	if (this->_spriteProvider)
		return static_cast<Sprite*>(this->_spriteProvider->getResource(name));
	return 0;
}

CoreFont	*GlobalResourceManager::getFont(std::string const &name) const
{
	if (this->_fontProvider)
		return static_cast<CoreFont*>(this->_fontProvider->getResource(name));
	return 0;
}

BulletMLParser	*GlobalResourceManager::getBulletParser(std::string const &name) const
{
	return static_cast<BulletMLParser*>(this->_bulletProvider.getResource(name));
}

Resource	*GlobalResourceManager::getResource(std::string const &) const
{
	return 0;
}

Resource	*GlobalResourceManager::getResource(std::string const &name, std::string const &providerName) const
{
	XMLProvider	*provider = this->getProvider(providerName);

	if (provider)
		return provider->getResource(name);
	return 0;
}

void		GlobalResourceManager::handleXML(TiXmlNode *parent, ResourceManager &manager)
{
	static Method<TiXmlNode::NodeType> const	methods[] = {
			{TiXmlNode::DOCUMENT, &GlobalResourceManager::loadDocument},
			{TiXmlNode::ELEMENT, &GlobalResourceManager::loadElement},
			{TiXmlNode::COMMENT, &GlobalResourceManager::loadComment},
			{TiXmlNode::UNKNOWN, &GlobalResourceManager::loadUnknown},
			{TiXmlNode::TEXT, &GlobalResourceManager::loadText},
			{TiXmlNode::DECLARATION, &GlobalResourceManager::loadDeclaration}
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
				(this->*methods[i].func)(child, manager);
				break ;
			}
		}
	}
}

void		GlobalResourceManager::loadDocument(TiXmlNode *parent, ResourceManager &manager)
{
  this->handleXML(parent, manager);
}

void		GlobalResourceManager::loadElement(TiXmlNode *parent, ResourceManager &manager)
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
		      (*it).second->handleXML(child, manager);
		      break ;
		    }
		}
	}
}

void		GlobalResourceManager::loadComment(TiXmlNode *, ResourceManager &)
{
}

void		GlobalResourceManager::loadUnknown(TiXmlNode *, ResourceManager &)
{
}

void		GlobalResourceManager::loadText(TiXmlNode *, ResourceManager &)
{
}

void		GlobalResourceManager::loadDeclaration(TiXmlNode *, ResourceManager &)
{
}

void		GlobalResourceManager::get2Int(std::string const &data,
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
