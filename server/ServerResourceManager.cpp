#include "ServerResourceManager.hpp"
#include "Resources.hpp"

ServerResourceManager::ServerResourceManager() : _id(1)
{
	for (int i = 0; i < Resources::SHOOT - Resources::SINGLE_MONSTER; ++i)
	{
		this->_ids[Resources::monsters[i].sprite] = Resources::SINGLE_MONSTER + i;
	}
}

ServerResourceManager::~ServerResourceManager()
{
}

Core::Sprite		*ServerResourceManager::addSprite(
				std::string const &name)
{
	if (this->_ids.find(name) == this->_ids.end())
		this->_ids[name] = _id++;
	return new Core::Sprite;
}

Core::Sprite		*ServerResourceManager::getSprite(
				std::string const &) const
{
	return 0;
}

void		ServerResourceManager::addImage(
						std::string const &path, Core::Sprite &)
{
	if (this->_resources.find(path) == this->_resources.end())
	{
	  Core::File	*file = new Core::File;
		if (file->load(path))
			this->_resources[path] = file;
		else
			delete file;
	}
}

uint32_t	ServerResourceManager::getId(std::string const &name) const
{
	std::map<std::string, uint32_t>::const_iterator it = _ids.find(name);

	if (it != this->_ids.end())
		return it->second;
	return 4;
}
