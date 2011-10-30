#pragma once

#include <string>
#include <map>

typedef std::string	BulletName;

struct	BulletResource
{
  BulletResource(std::string const &commandSprite, std::string const &simpleSprite,
		 std::string const &commandGroup, std::string const &simpleGroup);
  std::string		commandSprite;
  std::string		simpleSprite;
  std::string		commandGroup;
  std::string		simpleGroup;
};

typedef std::map<BulletName, BulletResource*>	bulletResources;

class BulletResourceManager
{
  public:
    BulletResourceManager();
    virtual ~BulletResourceManager();
    void		addBulletResource(BulletName const &name,
		   	std::string const &commandSprite, std::string const &simpleSprite,
			std::string const &commandGroup, std::string const &simpleGroup);

    //setter
    void		setBulletCommandSprite(BulletName const &name,
		    			std::string const &sprite);
    void		setBulletSimpleSprite(BulletName const &name,
		    		      std::string const &sprite);
    void		setBulletCommandGroup(BulletName const &name,
		    		       std::string const &group);
    void		setBulletSimpleGroup(BulletName const &name,
		    		       std::string const &group);


    //getter
    std::string const		&getBulletCommandSprite(BulletName const &name) const;
    std::string const		&getBulletSimpleSprite(BulletName const &name) const;
    std::string const		&getBulletCommandGroup(BulletName const &name) const;
    std::string const		&getBulletSimpleGroup(BulletName const &name) const;
    BulletResource const	&getBulletResource(BulletName const &name) const;

  private:
    bulletResources		_resources;
};
