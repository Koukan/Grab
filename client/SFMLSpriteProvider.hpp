#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteProvider.hpp"
#include "SFMLSprite.hpp"

class SFMLSpriteProvider : public SpriteProvider
{
  public:
    SFMLSpriteProvider();
    virtual ~SFMLSpriteProvider();
	virtual Sprite		*addSprite(std::string const &name);
	virtual void		addImage(std::string const &path, Sprite &sprite);
	virtual Resource	*getResource(std::string const &name) const;
	virtual void		deleteResource(std::string const &name);

  private:
	typedef	std::map<std::string, std::pair<SFMLSprite*, std::string> >	SpritesMap;
	#if SFML_VERSION_MAJOR == 2
	typedef	std::map<std::string, sf::Texture*>	ImagesMap;
	#else
	typedef std::map<std::string, sf::Image*>	ImagesMap;
	#endif
	typedef	std::map<std::string, int>			UseMap;

	SpritesMap		_sprites;
	ImagesMap		_images;
	UseMap			_use;
};
