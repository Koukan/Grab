#pragma once

#include <map>
#include "tinyxml.h"
#include "Sprite.hpp"
#include "Font.hpp"
#include "bulletmlparser.h"
#include "XMLProvider.hpp"
#include "Singleton.hpp"

class SpriteProvider;
class FontProvider;
class BulletResourceManager;

class GlobalResourceManager : public XMLProvider, public Net::Singleton<GlobalResourceManager>
{
  public:
	GlobalResourceManager();
	virtual ~GlobalResourceManager();
	void			init();
	void			load(std::string const &path, ResourceManager &manager);
	void			addProvider(XMLProvider &provider);
	BulletMLParser	*addBulletParser(std::string const &path, std::string const &name, ResourceManager &manager);
	XMLProvider		*getProvider(std::string const &name) const;
	XMLProvider		*getProvider(uint32_t type) const;
	Sprite			*getSprite(std::string const &name) const;
	CoreFont		*getFont(std::string const &name) const;
	BulletMLParser	*getBulletParser(std::string const &name) const;
	Resource		*getResource(std::string const &name, std::string const &provider) const;
	Resource		*getResource(std::string const &name, uint32_t type) const;

	template <typename T>
	struct			Method
	{
		T			name;
		void		(GlobalResourceManager::*func)(TiXmlNode *, ResourceManager &);
	};

  private:
	typedef std::map<std::string, XMLProvider *>	ProviderMap;
	typedef std::map<uint32_t, XMLProvider *>		IdMap;

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
	BulletResourceManager	*_bulletProvider;
	ProviderMap				_providers;
	IdMap					_ids;
	TiXmlDocument			_document;
};
