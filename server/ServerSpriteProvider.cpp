#include "ServerSpriteProvider.hpp"

ServerSpriteProvider::ServerSpriteProvider()
{
}

ServerSpriteProvider::~ServerSpriteProvider()
{
}

Core::Sprite		*ServerSpriteProvider::addSprite(std::string const &)
{
	return 0;
}

void				ServerSpriteProvider::addSprite(std::string const &name, Core::Sprite &sprite)
{
	ResourceMap::iterator	it = this->_resources.find(name);

	if (it == this->_resources.end())
		this->XMLProvider::addResource(name, sprite);
}

void				ServerSpriteProvider::addImage(std::string const &, Core::Sprite &)
{
}
