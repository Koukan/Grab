#pragma once

#include <map>
#include "tinyxml.h"
#include "Sprite.hpp"
#include "Font.hpp"
#include "Sound.hpp"
#include "bulletmlparser.h"
#include "XMLProvider.hpp"
#include "Singleton.hpp"

CORE_BEGIN_NAMESPACE

class SpriteProvider;
class FontProvider;
class BulletResourceManager;

class CORE_DLLREQ GlobalResourceManager : public XMLProvider, public Net::Singleton<GlobalResourceManager>
{
  public:
	GlobalResourceManager();
	virtual ~GlobalResourceManager();
	void			init();
	void			load(std::string const &path, ResourceManager &manager);
	void			addProvider(XMLProvider &provider);
	BulletMLParser	*addBulletParser(std::string const &path, std::string const &name, ResourceManager &manager);

	// getter
	XMLProvider		*getProvider(std::string const &name) const;
	XMLProvider		*getProvider(uint8_t type) const;
	Sprite			*getSprite(std::string const &name) const;
	Sprite			*getSprite(uint32_t id) const;
	CoreFont		*getFont(std::string const &name) const;
	CoreFont		*getFont(uint32_t id) const;
	BulletMLParser	*getBulletParser(std::string const &name) const;
	BulletMLParser	*getBulletParser(uint32_t id) const;
	Sound           *getSound(std::string const &name) const;
	Sound           *getSound(uint32_t id) const;
	Resource		*getResource(std::string const &name, std::string const &provider) const;
	Resource		*getResource(std::string const &name, uint8_t type) const;
	Resource		*getResource(uint32_t id, uint8_t type) const;

	void			changeId(std::string const &name, uint32_t id, uint8_t type);
	void			changeId(uint32_t oldId, uint32_t newId, uint8_t type);

	template <typename T>
	struct			Method
	{
		T			name;
		void		(GlobalResourceManager::*func)(TiXmlNode *, ResourceManager &);
	};

  private:
	typedef std::map<std::string, XMLProvider *>	ProviderMap;
	typedef std::map<uint8_t, XMLProvider *>		IdMap;

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
};

CORE_END_NAMESPACE
