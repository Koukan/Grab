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
	std::string		mapName;
	double			scrollingSpeed = 0;
	bool			random = false;

	_current = 0;
	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "name")
			mapName = attrib->Value();
		else if (name == "background")
		{}
		else if (name == "scrollingSpeed")
			scrollingSpeed = Net::Converter::toInt<double>(attrib->Value());
		else if (name == "random" && attrib->Value() == "true")
			random = true;
	}
	if (random)
		_current = new MonsterGenerator(/*seed*/-4098);
	else
		_current = new Map();
	this->addResource(mapName, *_current, manager);
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
			else if (name == "sound")
				this->handleSound(child, manager);
			else if (name == "end")
				this->handleEnd(child, manager);
			else if (name == "randomMonster")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomMonster);
			else if (name == "randomBoss")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomBoss);
			else if (name == "randomWall")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomWall);
			else if (name == "randomBreakableWall")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomBreakableWall);
		}
	}
	_current = 0;
}

void    MapProvider::handleEnd(TiXmlNode *parent, Core::ResourceManager &manager)
{
	this->handleElem(parent, manager, &Map::addEnd);
}

void    MapProvider::handleMonster(TiXmlNode *parent, Core::ResourceManager &manager)
{
	this->handleElem(parent, manager, &Map::addMonster);
}

void    MapProvider::handleDeco(TiXmlNode *parent, Core::ResourceManager &manager)
{
	this->handleElem(parent, manager, &Map::addDecoration);
}

void    MapProvider::handleSound(TiXmlNode *parent, Core::ResourceManager &manager)
{
	this->handleElem(parent, manager, &Map::addSound);
}

void    MapProvider::handleElem(TiXmlNode *parent, Core::ResourceManager &, void (Map::*func)(std::string const &name, size_t, size_t, int, int, bool, bool, int))
{
	std::string     name, monstername;
	size_t          y = 0, x = 0;
	int				vx = 0, vy = 0, spawnY = 0;
	bool			scrollable = true, pause = false;

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
		else if (name == "scrollable" && attrib->Value() == "false")
			scrollable = false;
		else if (name == "spawnY")
			spawnY = Net::Converter::toInt<int>(attrib->Value());
		else if (name == "pause" && attrib->Value() == "true")
			pause = true;
	}
	if (!monstername.empty())
	  (_current->*func)(monstername, x, y, vx, vy, scrollable, pause, spawnY);
}

void	MapProvider::handleRandomElem(TiXmlNode *parent, Core::ResourceManager &, void (MonsterGenerator::*func)(std::string const &name, bool scrollable, size_t level))
{
	std::string     name, monstername;
	bool			scrollable = true;
	size_t			level = 1;

	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "name")
			monstername = attrib->Value();
		else if (name == "scrollable" && attrib->Value() == "false")
			scrollable = false;
		else if (name == "level")
			level = Net::Converter::toInt<size_t>(attrib->Value());;
	}
	MonsterGenerator *gen;
	if (!monstername.empty() && (gen = dynamic_cast<MonsterGenerator *>(_current)))
	  (gen->*func)(monstername, scrollable, level);
}
