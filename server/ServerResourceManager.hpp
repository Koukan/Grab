#pragma once

#include <string>
#include "SpriteProvider.hpp"
#include "Singleton.hpp"
#include "ResourceManager.hpp"
#include "File.hpp"

class ServerResourceManager : public Net::Singleton<ServerResourceManager>, public Core::SpriteProvider, public Core::ResourceManager
{
  public:
    ServerResourceManager();
    virtual ~ServerResourceManager();
  virtual Core::Sprite	*addSprite(std::string const &);
  virtual Core::Sprite	*getSprite(std::string const &) const;
  virtual void	addImage(std::string const &path, Core::Sprite &);
	//void			loadResource(std::string const &path);

	//getter
	uint32_t		getId(std::string const &path) const;

  private:
	uint32_t						_id;
  std::map<std::string, Core::File*>	_resources;
	std::map<std::string, uint32_t> _ids;
};
