#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteProvider.hpp"
#include "SFMLSprite.hpp"

class SFMLSpriteProvider : public Core::SpriteProvider
{
  public:
    SFMLSpriteProvider();
    virtual ~SFMLSpriteProvider();
  virtual Core::Sprite		*addSprite(std::string const &name);
  virtual void		addImage(std::string const &path, Core::Sprite &sprite);
	virtual void		deleteResource(std::string const &name);

  private:
	#if SFML_VERSION_MAJOR == 2
	typedef	std::map<std::string, sf::Texture*>	ImagesMap;
	#else
	typedef std::map<std::string, sf::Image*>	ImagesMap;
	#endif
	typedef	std::map<std::string, int>			UseMap;
	typedef std::map<std::string, std::string>	SpriteMap;

	SpriteMap		_sprites;
	ImagesMap		_images;
	UseMap			_use;
};
