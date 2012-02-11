#pragma once

#include <map>
#include "BulletResourceManager.hpp"
#include "tinyxml.h"
#include "Sprite.hpp"
#include "Font.hpp"
#include "XMLProvider.hpp"
#include "Singleton.hpp"

class SpriteProvider;
class FontProvider;

class GlobalResourceManager : public XMLProvider, public Singleton<GlobalResourceManager>
{
  public:
	GlobalResourceManager();
	virtual ~GlobalResourceManager();
	void			load(std::string const &path, ResourceManager &manager);
	void			addProvider(XMLProvider &provider);
	BulletMLParser	*addBulletParser(std::string const &path, std::string const &name);
	XMLProvider		*getProvider(std::string const &name) const;
	Sprite			*getSprite(std::string const &name) const;
	CoreFont		*getFont(std::string const &name) const;
	BulletMLParser	*getBulletParser(std::string const &name) const;
	Resource		*getResource(std::string const &name) const;
	Resource		*getResource(std::string const &name, std::string const &provider) const;

	template <typename T>
	struct			Method
	{
		T			name;
		void		(GlobalResourceManager::*func)(TiXmlNode *, ResourceManager &);
	};

  private:
	typedef std::map<std::string, XMLProvider *> ProviderMap;

	void			handleXML(TiXmlNode *parent, ResourceManager &manager);
	void			loadDocument(TiXmlNode *parent, ResourceManager &manager);
	void			loadElement(TiXmlNode *parent, ResourceManager &manager);
	void			loadComment(TiXmlNode *parent, ResourceManager &manager);
	void			loadUnknown(TiXmlNode *parent, ResourceManager &manager);
	void			loadText(TiXmlNode *parent, ResourceManager &manager);
	void			loadDeclaration(TiXmlNode *parent, ResourceManager &manager);
	void			loadSprite(TiXmlNode *parent, ResourceManager &manager);
	void			get2Int(std::string const &data, std::string const &sep,
							int &a, int &b);

	SpriteProvider			*_spriteProvider;
	FontProvider			*_fontProvider;
	BulletResourceManager	_bulletProvider;
	ProviderMap				_providers;
	TiXmlDocument			_document;
};
