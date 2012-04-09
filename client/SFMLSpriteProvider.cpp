#include <iostream>
#include "SFMLSpriteProvider.hpp"

SFMLSpriteProvider::SFMLSpriteProvider()
{
}

SFMLSpriteProvider::~SFMLSpriteProvider()
{
}

Core::Sprite		*SFMLSpriteProvider::addSprite(std::string const &name)
{
	ResourceMap::iterator	it = this->_resources.find(name);

	if (it == this->_resources.end())
	  return new SFMLSprite;
	else
	  return static_cast<Core::Sprite*>(it->second);
}

void		SFMLSpriteProvider::addImage(std::string const &path, Core::Sprite &sprite)
{
	ImagesMap::iterator	it = this->_images.find(path);

	#if SFML_VERSION_MAJOR == 2
	#define SETTEXTURE(a) (static_cast<SFMLSprite*>(&sprite)->SetTexture(a));
	#else

	#define SETTEXTURE(a) (static_cast<SFMLSprite*>(&sprite)->SetImage(a));
	#endif
	if (it == this->_images.end())
	{
		#if SFML_VERSION_MAJOR == 2
		sf::Texture	*texture = new sf::Texture;
		#else
		sf::Image	*texture = new sf::Image;
		#endif
		if (!texture->LoadFromFile(path))
			std::cerr << "Image at " << path << " was not found." << std::endl;
		texture->SetSmooth(false);
		this->_images[path] = texture;
		this->_use[path] = 1;
		SETTEXTURE(*texture);
	}
	else
	{
		SETTEXTURE(*it->second);
		if (this->_sprites[sprite.getResourceName()].empty())
			this->_use[path]++;
	}
	this->_sprites[sprite.getResourceName()] = path;
	sprite.setCenter();
}

void		SFMLSpriteProvider::deleteResource(std::string const &name)
{
	SpriteMap::iterator	it = this->_sprites.find(name);

	if (it != this->_sprites.end())
	{
		UseMap::iterator lit = this->_use.find(it->second);

		if (lit != this->_use.end())
		{
			lit->second--;
			if (!lit->second)
			{
				ImagesMap::iterator pit = this->_images.find(it->second);

				if (pit != this->_images.end())
				{
					delete pit->second;
					this->_images.erase(pit);
					this->_use.erase(lit);
				}
			}
		}
		this->_sprites.erase(it);
		this->XMLProvider::deleteResource(name);
	}
}
