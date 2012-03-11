#pragma once

#include "SpriteProvider.hpp"

class ServerSpriteProvider : public Core::SpriteProvider
{
  public:
    ServerSpriteProvider();
    virtual ~ServerSpriteProvider();

	Core::Sprite	*addSprite(std::string const &name);
	void			addSprite(std::string const &name, Core::Sprite &sprite);
	void			addImage(std::string const &, Core::Sprite &);
};
