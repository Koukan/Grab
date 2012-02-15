#include <iostream>
#include <stdexcept>
#include "GlobalResourceManager.hpp"
#include "Sprite.hpp"
#include "Font.hpp"
#include "Converter.hpp"
#include "LoadXMLProvider.hpp"
#include "SpriteProvider.hpp"
#include "FontProvider.hpp"
#include "BulletResourceManager.hpp"

CORE_USE_NAMESPACE

GlobalResourceManager::GlobalResourceManager()
  : XMLProvider("resources", 0), _spriteProvider(0), _fontProvider(0), _bulletProvider(0)
{
	this->addProvider(*this);
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

void		GlobalResourceManager::init()
{
	this->addProvider(*new BulletResourceManager());
	this->addProvider(*new LoadXMLProvider());
}

void		GlobalResourceManager::load(std::string const &path, ResourceManager &manager)
{
	if (!this->_document.LoadFile(path.c_str()))
		throw std::runtime_error(path + ": not found");
	this->handleXML(&this->_document, manager);
}

void		GlobalResourceManager::addProvider(XMLProvider &provider)
{
	if (provider.handledTag == "sprite")
	{
		if (!this->_spriteProvider)
			this->_spriteProvider = static_cast<SpriteProvider*>(&provider);
	}
	else if (provider.handledTag == "font")
	{
		if (!this->_fontProvider)
			this->_fontProvider = static_cast<FontProvider*>(&provider);
	}
	else if (provider.handledTag == "bulletml")
	{
		if (!this->_bulletProvider)
			this->_bulletProvider = static_cast<BulletResourceManager*>(&provider);
	}
	if (this->_providers.find(provider.handledTag) == this->_providers.end())
	{
		this->_providers[provider.handledTag] = &provider;
		if (provider.type != 0)
			this->_ids[provider.type] = &provider;
	}
}

BulletMLParser	*GlobalResourceManager::addBulletParser(std::string const &path,
										std::string const &name, ResourceManager &manager)
{
	if (this->_bulletProvider)
		return this->_bulletProvider->addBulletParser(path, name, manager);
	return 0;
}

XMLProvider	*GlobalResourceManager::getProvider(std::string const &name) const
{
	ProviderMap::const_iterator	it = this->_providers.find(name);

	if (it != this->_providers.end())
		return it->second;
	return 0;
}

XMLProvider	*GlobalResourceManager::getProvider(uint32_t type) const
{
	IdMap::const_iterator	it = this->_ids.find(type);

	if (it != this->_ids.end())
		return it->second;
	return 0;
}

Sprite		*GlobalResourceManager::getSprite(std::string const &name) const
{
	if (this->_spriteProvider)
		return static_cast<Sprite*>(this->_spriteProvider->getResource(name));
	return 0;
}

Sprite		*GlobalResourceManager::getSprite(uint32_t id) const
{
	if (this->_spriteProvider)
		return static_cast<Sprite*>(this->_spriteProvider->getResource(id));
	return 0;
}

CoreFont	*GlobalResourceManager::getFont(std::string const &name) const
{
	if (this->_fontProvider)
		return static_cast<CoreFont*>(this->_fontProvider->getResource(name));
	return 0;
}

CoreFont	*GlobalResourceManager::getFont(uint32_t id) const
{
	if (this->_fontProvider)
		return static_cast<CoreFont*>(this->_fontProvider->getResource(id));
	return 0;
}

BulletMLParser	*GlobalResourceManager::getBulletParser(std::string const &name) const
{
	if (this->_bulletProvider)
		return static_cast<BulletMLParser*>(this->_bulletProvider->getResource(name));
	return 0;
}

BulletMLParser	*GlobalResourceManager::getBulletParser(uint32_t id) const
{
	if (this->_bulletProvider)
		return static_cast<BulletMLParser*>(this->_bulletProvider->getResource(id));
	return 0;
}

Resource	*GlobalResourceManager::getResource(std::string const &name, std::string const &providerName) const
{
	XMLProvider	*provider = this->getProvider(providerName);

	if (provider)
		return provider->getResource(name);
	return 0;
}

Resource	*GlobalResourceManager::getResource(std::string const &name, uint8_t type) const
{
	XMLProvider	*provider = this->getProvider(type);

	if (provider)
		return provider->getResource(name);
	return 0;
}

Resource	*GlobalResourceManager::getResource(uint32_t id, uint8_t type) const
{
	XMLProvider	*provider = this->getProvider(type);

	if (provider)
		return provider->getResource(id);
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

	a = Net::Converter::toInt<int>(data);
	if (pos == std::string::npos)
		b = 0;
	else
	  b = Net::Converter::toInt<int>(data.substr(pos + sep.size()));
}
