#pragma once

#include <stdint.h>
#include "Sprite.hpp"
#include "XMLProvider.hpp"
#include "tinyxml.h"

class SpriteProvider : public XMLProvider
{
public:
  template <typename T>
  struct			Method
  {
    std::string	name;
    void		(SpriteProvider::*func)(TiXmlElement*, T);
  };

  template <typename T>
  void			loadElement(TiXmlNode *parent, T data,
				    Method<T> const *tab, size_t sizeTab);

  SpriteProvider();
  virtual ~SpriteProvider(){}
  virtual Sprite	*addSprite(std::string const &) = 0;
  virtual Sprite	*getSprite(std::string const &) const = 0;
  virtual void		addImage(std::string const &/*path*/, Sprite &) = 0;
  virtual void		handleXML(TiXmlNode *);

private:
  // handle xml

  void    imageSprite(TiXmlElement *parent, Sprite *sprite);
  void    animationSprite(TiXmlElement *parent, Sprite *sprite);
  void    scaleSprite(TiXmlElement *parent, Sprite *sprite);
  void    translateSprite(TiXmlElement *parent, Sprite *sprite);
  void	  gridSprite(TiXmlElement *parent, Sprite *sprite);
  void	  get2Int(std::string const &data,
		  std::string const &sep,
		  int &a, int &b);
};

#include "SpriteProvider.ipp"
