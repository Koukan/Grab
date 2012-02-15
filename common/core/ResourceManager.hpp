#pragma once

#include <map>
#include "Resource.hpp"
#include "Sprite.hpp"
#include "Font.hpp"
#include "bulletmlparser.h"
#include "CoreDef.hpp"

CORE_BEGIN_NAMESPACE

class ResourceManager
{
  public:
	ResourceManager();
	virtual ~ResourceManager();
	void			load(std::string const &path);
	Sprite			*getSprite(std::string const &name) const;
	CoreFont		*getFont(std::string const &name) const;
	BulletMLParser	*getBulletParser(std::string const &name) const;
	Resource		*getResource(std::string const &name, uint8_t type) const;
	Sprite			*getSprite(uint32_t id) const;
	CoreFont		*getFont(uint32_t id) const;
	BulletMLParser	*getBulletMLParser(uint32_t id) const;
	Resource		*getResource(uint32_t id, uint8_t type) const;

	void			addBulletParser(std::string const &path, std::string const &name);
	void			addResource(Resource &resource);

	private:
	typedef	std::list<Resource *>	ResourceList;

	ResourceList			_resources;
};

CORE_END_NAMESPACE
