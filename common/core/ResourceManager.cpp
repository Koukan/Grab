#include "ResourceManager.hpp"
#include "XMLProvider.hpp"
#include "GlobalResourceManager.hpp"
#include <iostream>

CORE_USE_NAMESPACE

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (ResourceList::iterator it = this->_resources.begin();
		 it != this->_resources.end(); it++)
		(*it)->removeUse();
}

void		ResourceManager::load(std::string const &path)
{
	GlobalResourceManager::get().load(path, *this);
}

void		ResourceManager::changeId(std::string const &name, uint32_t id, uint8_t type)
{
	GlobalResourceManager::get().changeId(name, id, type);
}

void		ResourceManager::changeId(uint32_t oldId, uint32_t newId, uint8_t type)
{
	GlobalResourceManager::get().changeId(oldId, newId, type);
}

Sprite		*ResourceManager::getSprite(std::string const &name) const
{
	return GlobalResourceManager::get().getSprite(name);
}

CoreFont	*ResourceManager::getFont(std::string const &name) const
{
	return GlobalResourceManager::get().getFont(name);
}

BulletMLParser	*ResourceManager::getBulletParser(std::string const &name) const
{
	return GlobalResourceManager::get().getBulletParser(name);
}

Sound			*ResourceManager::getSound(std::string const &name) const
{
	return GlobalResourceManager::get().getSound(name);
}

Resource	*ResourceManager::getResource(std::string const &name, uint8_t type) const
{
	return GlobalResourceManager::get().getResource(name, type);
}

Sprite			*ResourceManager::getSprite(uint32_t id) const
{
	return GlobalResourceManager::get().getSprite(id);
}

CoreFont		*ResourceManager::getFont(uint32_t id) const
{
	return GlobalResourceManager::get().getFont(id);
}

BulletMLParser	*ResourceManager::getBulletMLParser(uint32_t id) const
{
	return GlobalResourceManager::get().getBulletParser(id);
}

Resource		*ResourceManager::getResource(uint32_t id, uint8_t type) const
{
	return GlobalResourceManager::get().getResource(id, type);
}

std::list<Resource*> const	&ResourceManager::getResource() const
{
	return this->_resources;
}

void		ResourceManager::addBulletParser(std::string const &path,
											 std::string const &name)
{
	GlobalResourceManager::get().addBulletParser(path, name, *this);
}

void		ResourceManager::addResource(Resource &resource)
{
	this->_resources.push_back(&resource);
	resource.addUse();
}
