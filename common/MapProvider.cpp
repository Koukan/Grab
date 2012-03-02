#include "MapProvider.hpp"
#include "Converter.hpp"

MapProvider::MapProvider() : XMLProvider("map", 5)
{
}

MapProvider::~MapProvider()
{
}

void    MapProvider::handleXML(TiXmlNode *parent, Core::ResourceManager &manager)
{
	std::string		name;
	double			scrollingSpeed = 0;

	_current = 0;
	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "name")
		{
			_current = new Map();
			this->addResource(attrib->Value(), *_current, manager);
		}
		else if (name == "background")
		{}
		else if (name == "scrollingSpeed")
			scrollingSpeed = Net::Converter::toInt<double>(attrib->Value());
	}
	if (!_current)
		return ;
	else
		_current->setVy(scrollingSpeed);
	for (TiXmlNode *child = parent->FirstChild(); child != 0;
		 child = child->NextSibling())
	{
		if (child->Type() == TiXmlNode::ELEMENT)
		{
			name = child->Value();
			if (name == "monster")
				this->handleMonster(child, manager);
			else if (name == "deco")
				this->handleDeco(child, manager);
		}
	}
	_current = 0;
}

void    MapProvider::handleMonster(TiXmlNode *parent, Core::ResourceManager &manager)
{
	this->handleElem(parent, manager, &Map::addMonster);
}

void    MapProvider::handleDeco(TiXmlNode *parent, Core::ResourceManager &manager)
{
	this->handleElem(parent, manager, &Map::addDecoration);
}

void    MapProvider::handleElem(TiXmlNode *parent, Core::ResourceManager &, void (Map::*func)(std::string const &name, size_t, size_t, int, int))
{
	std::string     name, monstername;
	size_t          y = 0, x = 0;
	int				vx = 0, vy = 0;

	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "name")
			monstername = attrib->Value();
		else if (name == "y")
			y = Net::Converter::toInt<size_t>(attrib->Value());
		else if (name == "x")
			x = Net::Converter::toInt<size_t>(attrib->Value());
		else if (name == "vx")
			vx = Net::Converter::toInt<int>(attrib->Value());
		else if (name == "vy")
			vy = Net::Converter::toInt<int>(attrib->Value());
	}
	if (!monstername.empty())
		(_current->*func)(monstername, x, y, vx, vy);
}

