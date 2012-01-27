#include <iostream>
#include "SpriteProvider.hpp"
#include "Converter.hpp"

SpriteProvider::SpriteProvider()
  : XMLProvider("sprite")
{
}

void	SpriteProvider::handleXML(TiXmlNode *parent)
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
			sprite = this->addSprite(attrib->Value());
	}
	if (sprite)
		this->loadElement(static_cast<TiXmlElement*>(parent), sprite,
						  methods, sizeof(methods) / sizeof(*methods));
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
			x = Converter::toInt<float>(attrib->Value());
		else if (name == "y")
			y = Converter::toInt<float>(attrib->Value());
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
			sprite->setSpeed(Converter::toInt<double>(attrib->Value()));
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
			x = Converter::toInt<int>(attrib->Value());
		else if (name == "y")
			y = Converter::toInt<int>(attrib->Value());
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

	a = Converter::toInt<int>(data);
	if (pos == std::string::npos)
		b = 0;
	else
		b = Converter::toInt<int>(data.substr(pos + sep.size()));
}
