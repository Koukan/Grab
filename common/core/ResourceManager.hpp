#pragma once

#include <map>
#include <list>
#include "BulletResourceManager.hpp"
#include "tinyxml.h"
#include "Sprite.hpp"
#include "Font.hpp"
#include "XMLProvider.hpp"

class ResourceManager : public BulletResourceManager, public XMLProvider
{
  public:
	ResourceManager();
	virtual ~ResourceManager();
	void			load(std::string const &path);
	void			addProvider(XMLProvider &provider);
	Sprite			*getSprite(std::string const &name) const;
	Font			*getFont(std::string const &name) const;

  template <typename T>
  struct			Method
  {
    T			name;
    void		(ResourceManager::*func)(TiXmlNode *);
  };

  private:
	typedef std::map<std::string, XMLProvider *> ProviderMap;

	void			handleXML(TiXmlNode *parent);
	void			loadDocument(TiXmlNode *parent);
	void			loadElement(TiXmlNode *parent);
	void			loadComment(TiXmlNode *parent);
	void			loadUnknown(TiXmlNode *parent);
	void			loadText(TiXmlNode *parent);
	void			loadDeclaration(TiXmlNode *parent);
	void			loadSprite(TiXmlNode *parent);
	void			get2Int(std::string const &data, std::string const &sep,
							int &a, int &b);

	ProviderMap	_providers;
	TiXmlDocument	_document;
};
