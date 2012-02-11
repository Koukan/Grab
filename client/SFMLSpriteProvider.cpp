#include <iostream>
#include "SFMLSpriteProvider.hpp"

SFMLSpriteProvider::SFMLSpriteProvider()
{
}

SFMLSpriteProvider::~SFMLSpriteProvider()
{
	//for (SpritesMap::iterator it = this->_sprites.begin();
		 //it != this->_sprites.end(); it++)
	//{
		//delete it->second;
	//}
	//for (ImagesMap::iterator it = this->_images.begin();
		 //it != this->_images.end(); it++)
	//{
		//delete it->second;
	//}
}

Sprite		*SFMLSpriteProvider::addSprite(std::string const &name)
{
	SFMLSprite				*sprite = 0;
	SpritesMap::iterator	it = this->_sprites.find(name);

	if (it == this->_sprites.end())
	{
		sprite = new SFMLSprite;
		this->_sprites[name].first = sprite;
	}
	else
		sprite = it->second.first;
	return sprite;
}

void		SFMLSpriteProvider::addImage(std::string const &path, Sprite &sprite)
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
		this->_images[path] = texture;
		this->_use[path] = 1;
		SETTEXTURE(*texture);
	}
	else
	{
		SETTEXTURE(*it->second);
		if (this->_sprites[sprite.getResourceName()].second.empty())
			this->_use[path]++;
	}
	this->_sprites[sprite.getResourceName()].second = path;
}

Resource	*SFMLSpriteProvider::getResource(std::string const &name) const
{
	SFMLSprite					*sprite = 0;
	SpritesMap::const_iterator	it = this->_sprites.find(name);

	if (it != this->_sprites.end())
		sprite = new SFMLSprite(*it->second.first);
	return sprite;
}

void		SFMLSpriteProvider::deleteResource(std::string const &name)
{
	SpritesMap::iterator	it = this->_sprites.find(name);

	if (it != this->_sprites.end())
	{
		UseMap::iterator lit = this->_use.find(it->second.second);

		if (lit != this->_use.end())
		{
			lit->second--;
			if (!lit->second)
			{
				ImagesMap::iterator pit = this->_images.find(it->second.second);

				if (pit != this->_images.end())
				{
					delete pit->second;
					this->_images.erase(pit);
					this->_use.erase(lit);
				}
			}
		}
		this->_sprites.erase(it);
	}
}
