#include <iostream>
#include "SpriteProvider.hpp"
#include "Converter.hpp"

CORE_USE_NAMESPACE

SpriteProvider::SpriteProvider()
  : XMLProvider("sprite", 1)
{
}

void	SpriteProvider::handleXML(TiXmlNode *parent, ResourceManager &manager)
{
	static Method<Sprite*> const	methods[] = {
	  {"image", &SpriteProvider::imageSprite},
	  {"animation", &SpriteProvider::animationSprite},
	  {"scale", &SpriteProvider::scaleSprite},
	  {"translation", &SpriteProvider::translateSprite}
	};
	Sprite				*sprite = 0;
	std::string			name;

	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "name")
		{
			sprite = this->addSprite(attrib->Value());
			if (sprite)
			{
				this->XMLProvider::addResource(attrib->Value(), *sprite, manager);
				this->loadElement(static_cast<TiXmlElement*>(parent), sprite,
						  methods, sizeof(methods) / sizeof(*methods));
			}
		}
		else if (name == "transparency" && sprite)
		  {
		    sprite->setTransparency(Net::Converter::toInt<float>(attrib->Value()));
		  }
		else if (name == "color" && sprite)
		  {
			  int r;
			  int g;
			  int b;

			  this->get3Int(attrib->Value(), ",", r, g, b);
		    sprite->setColor(r, g, b);
		  }

	}
}

void	SpriteProvider::imageSprite(TiXmlElement *parent, Sprite *sprite)
{
	static Method<Sprite*> const	methods[] = {
	  {"grid", &SpriteProvider::gridSprite}
	};
	std::string name;

	for (TiXmlAttribute *attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "file")
			this->addImage(attrib->Value(), *sprite);
	}
	this->loadElement(parent, sprite, methods,
					  sizeof(methods) / sizeof(*methods));
}

void	SpriteProvider::scaleSprite(TiXmlElement *parent, Sprite *sprite)
{
	std::string	name;
	float		x = 1;
	float		y = 1;

	for (TiXmlAttribute	*attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "x")
		  x = Net::Converter::toInt<float>(attrib->Value());
		else if (name == "y")
		  y = Net::Converter::toInt<float>(attrib->Value());
	}
	sprite->setScale(x, y);
}

void	SpriteProvider::animationSprite(TiXmlElement *parent, Sprite *sprite)
{
	std::string	name;

	for (TiXmlAttribute	*attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "speed")
		  sprite->setSpeed(Net::Converter::toInt<double>(attrib->Value()));
		else if (name == "loop")
			sprite->setRepeat((attrib->Value() == "yes") ? true : false);
		else if (name == "pingpong")
			sprite->setPingpong((attrib->Value() == "yes") ? true : false);
	}
}

void	SpriteProvider::translateSprite(TiXmlElement *parent, Sprite *sprite)
{
	int			x = 0;
	int			y = 0;
	std::string	name;

	for (TiXmlAttribute	*attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "x")
		  x = Net::Converter::toInt<int>(attrib->Value());
		else if (name == "y")
		  y = Net::Converter::toInt<int>(attrib->Value());
	}
	sprite->setTranslate(x, y);
}

void	SpriteProvider::gridSprite(TiXmlElement *parent, Sprite *sprite)
{
	int			x = 0, y = 0;
	int			width = 0, height = 0;
	int			nbx = 0, nby = 0;
	int			spacex = 0, spacey = 0;
	std::string name;

	for (TiXmlAttribute *attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "pos")
			this->get2Int(attrib->Value(), ",", x, y);
		else if (name == "size")
			this->get2Int(attrib->Value(), ",", width, height);
		else if (name == "array")
			this->get2Int(attrib->Value(), ",", nbx, nby);
		else if (name == "spacing")
			this->get2Int(attrib->Value(), ",", spacex, spacey);
	}
	sprite->setGrid(x, y, width, height, nbx, nby, spacex, spacey);
}

void		SpriteProvider::get2Int(std::string const &data,
					std::string const &sep,
					int &a, int &b)
{
	size_t	pos = data.find(sep);

	a = Net::Converter::toInt<int>(data);
	if (pos == std::string::npos)
		b = 0;
	else
	  b = Net::Converter::toInt<int>(data.substr(pos + sep.size()));
}

void		SpriteProvider::get3Int(std::string const &data, std::string const &sep,
					 int &a, int &b, int &c)
{
	size_t	pos = data.find(sep);

	a = Net::Converter::toInt<int>(data);
	if (pos == std::string::npos)
		b = 0;
	else
	{
		std::string data2 = data.substr(pos + sep.size());
		size_t pos2 = data2.find(sep);
		b = Net::Converter::toInt<int>(data2);
		if (pos2 == std::string::npos)
			c = 0;
		else
			c = Net::Converter::toInt<int>(data2.substr(pos2 + sep.size()));
	}
}
