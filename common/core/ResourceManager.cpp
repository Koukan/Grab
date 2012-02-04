#include "ResourceManager.hpp"
#include "XMLProvider.hpp"
#include "GlobalResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (SpriteMap::iterator it = this->_sprites.begin();
		 it != this->_sprites.end(); it++)
		it->second->removeUse();
	for (FontMap::iterator it = this->_fonts.begin();
		 it != this->_fonts.end(); it++)
		it->second->removeUse();
	for (BulletMap::iterator it = this->_bullets.begin();
		 it != this->_bullets.end(); it++)
		it->second->removeUse();
	for (ResourceMap::iterator it = this->_resources.begin();
		 it != this->_resources.end(); it++)
		it->second->removeUse();
}

void		ResourceManager::load(std::string const &path)
{
	GlobalResourceManager::get().load(path, *this);
}

Sprite		*ResourceManager::getSprite(std::string const &name) const
{
	SpriteMap::const_iterator it = this->_sprites.find(name);

	if (it != this->_sprites.end())
		return static_cast<Sprite*>(it->second->clone());
	return 0;
}

CoreFont	*ResourceManager::getFont(std::string const &name) const
{
	FontMap::const_iterator it = this->_fonts.find(name);

	if (it != this->_fonts.end())
		return static_cast<CoreFont*>(it->second->clone());
	return 0;
}

BulletMLParser	*ResourceManager::getBulletParser(std::string const &name) const
{
	BulletMap::const_iterator it = this->_bullets.find(name);

	if (it != this->_bullets.end())
		return static_cast<BulletMLParser*>(it->second->clone());
	return 0;
}

Resource	*ResourceManager::getResource(std::string const &name) const
{
	ResourceMap::const_iterator it = this->_resources.find(name);

	if (it != this->_resources.find(name))
		return it->second->clone();
	return 0;
}

void		ResourceManager::addSprite(Sprite &sprite)
{
	this->_sprites[sprite.getResourceName()] = &sprite;
	sprite.addUse();
}

void		ResourceManager::addFont(CoreFont &font)
{
	this->_fonts[font.getResourceName()] = &font;
	font.addUse();
}

void		ResourceManager::addBulletParser(BulletMLParser &parser)
{
	this->_bullets[parser.getResourceName()] = &parser;
	parser.addUse();
}

void		ResourceManager::addBulletParser(std::string const &path,
											 std::string const &name)
{
	GlobalResourceManager::get().addBulletParser(path, name);
}

void		ResourceManager::addResource(Resource &resource)
{
	this->_resources[resource.getResourceName()] = &resource;
	resource.addUse();
}
