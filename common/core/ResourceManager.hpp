#pragma once

#include <map>
#include "Resource.hpp"
#include "Sprite.hpp"
#include "Font.hpp"
#include "bulletmlparser.h"

class ResourceManager
{
  public:
	ResourceManager();
	virtual ~ResourceManager();
	void			load(std::string const &path);
	Sprite			*getSprite(std::string const &name) const;
	CoreFont		*getFont(std::string const &name) const;
	BulletMLParser	*getBulletParser(std::string const &name) const;
	Resource		*getResource(std::string const &name) const;

	void			addSprite(Sprite &);
	void			addFont(CoreFont &);
	void			addBulletParser(BulletMLParser &);
	void			addBulletParser(std::string const &path, std::string const &name);
	void			addResource(Resource &);

  private:
	typedef std::map<std::string, Sprite*>			SpriteMap;
	typedef std::map<std::string, CoreFont*>		FontMap;
	typedef std::map<std::string, BulletMLParser*>	BulletMap;
	typedef std::map<std::string, Resource*>		ResourceMap;

	SpriteMap		_sprites;
	FontMap			_fonts;
	BulletMap		_bullets;
	ResourceMap		_resources;
};
