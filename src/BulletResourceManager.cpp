#include "BulletResourceManager.hpp"

BulletResource::BulletResource(std::string const &commandSprite,
		std::string const &simpleSprite, std::string const &commandGroup,
		std::string const &simpleGroup)
	: commandSprite(commandSprite), simpleSprite(simpleSprite),
	  commandGroup(commandGroup), simpleGroup(simpleGroup)
{
}

BulletResourceManager::BulletResourceManager()
{
  _resources["default"] = new BulletResource("default", "default", "default", "default");
}

BulletResourceManager::~BulletResourceManager()
{
  for (std::map<std::string, BulletResource*>::iterator it = _resources.begin();
       it != _resources.end(); it++)
    delete it->second;
}

void		BulletResourceManager::addBulletResource(std::string const &name,
		std::string const &commandSprite, std::string const &simpleSprite,
		std::string const &commandGroup, std::string const &simpleGroup)
{
  bulletResources::iterator	it = _resources.find(name);
  if (it == _resources.end())
    _resources[name] = new BulletResource(commandSprite, simpleSprite, commandGroup, simpleGroup);
  else
  {
    it->second->commandSprite = commandSprite;
    it->second->simpleSprite = simpleSprite;
    it->second->commandGroup = commandGroup;
    it->second->simpleGroup = simpleGroup;
  }
}

void		BulletResourceManager::setBulletCommandSprite(std::string const &name,
							std::string const &sprite)
{
  bulletResources::iterator	it = _resources.find(name);

  if (it != _resources.end())
    it->second->commandSprite = sprite;
}

void		BulletResourceManager::setBulletSimpleSprite(std::string const &name,
						     std::string const &sprite)
{
  bulletResources::iterator	it = _resources.find(name);

  if (it != _resources.end())
    it->second->simpleSprite = sprite;
}

void		BulletResourceManager::setBulletCommandGroup(std::string const &name,
						     std::string const &group)
{
  bulletResources::iterator	it = _resources.find(name);

  if (it != _resources.end())
    it->second->commandGroup = group;
}

void		BulletResourceManager::setBulletSimpleGroup(std::string const &name,
						     std::string const &group)
{
  bulletResources::iterator	it = _resources.find(name);

  if (it != _resources.end())
    it->second->simpleGroup = group;
}

std::string const	&BulletResourceManager::getBulletCommandSprite(
					std::string const &name) const
{
  return getBulletResource(name).commandSprite;
}

std::string const	&BulletResourceManager::getBulletSimpleSprite(
					std::string const &name) const
{
  return getBulletResource(name).simpleSprite;
}

std::string const	&BulletResourceManager::getBulletCommandGroup(
					std::string const &name) const
{
  return getBulletResource(name).commandGroup;
}

std::string const	&BulletResourceManager::getBulletSimpleGroup(
					std::string const &name) const
{
  return getBulletResource(name).simpleGroup;
}

BulletResource const	&BulletResourceManager::getBulletResource(std::string const &name) const
{
  bulletResources::const_iterator	it = _resources.find(name);

  if (it != _resources.end())
    return *it->second;
  return *_resources.find("default")->second;
}
