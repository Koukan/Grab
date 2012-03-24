#pragma once

#include <map>
#include "Resource.hpp"
#include "Sprite.hpp"
#include "Font.hpp"
#include "Sound.hpp"
#include "bulletmlparser.h"
#include "CoreDef.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ ResourceManager
{
  public:
	ResourceManager();
	virtual ~ResourceManager();
	void			load(std::string const &path);
	void			addBulletParser(std::string const &path, std::string const &name);
	void			addResource(Resource &resource);

	void			changeId(std::string const &name, uint32_t id, uint8_t type);
	void			changeId(uint32_t oldId, uint32_t newId, uint8_t type);

	// getter
	Sprite						*getSprite(std::string const &name) const;
	CoreFont					*getFont(std::string const &name) const;
	BulletMLParser				*getBulletParser(std::string const &name) const;
	Sound	                    *getSound(std::string const &name) const;
	Resource					*getResource(std::string const &name, uint8_t type) const;
	Sprite						*getSprite(uint32_t id) const;
	CoreFont					*getFont(uint32_t id) const;
	BulletMLParser				*getBulletMLParser(uint32_t id) const;
	Resource					*getResource(uint32_t id, uint8_t type) const;
	std::list<Resource*> const	&getResource() const;

  private:
	typedef	std::list<Resource *>	ResourceList;

	ResourceList			_resources;
};

CORE_END_NAMESPACE
