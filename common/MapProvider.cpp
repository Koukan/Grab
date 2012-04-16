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
	double			scrollingSpeed = 50;
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
	ResourceMap::iterator	it = this->_resources.find(mapName);
	if (it != this->_resources.end())
	{
		_current = static_cast<Map*>(it->second);
		_current->clear();
	}
	else
		_current = (random) ? new MonsterGenerator(0) : new Map();
	this->addResource(mapName, *_current, manager);
	_current->setScrollingSpeed(scrollingSpeed);
	for (TiXmlNode *child = parent->FirstChild(); child;
		 child = child->NextSibling())
	{
		if (child->Type() == TiXmlNode::ELEMENT)
		{
			name = child->Value();
			if (name == "monster")
				this->handleElem(child, manager, &Map::addMonster);
			else if (name == "compositemonster")
				this->handleElem(child, manager, &Map::addCompositeMonster);
			else if (name == "deco")
				this->handleElem(child, manager, &Map::addDecoration);
			else if (name == "sound")
				this->handleElem(child, manager, &Map::addSound);
			else if (name == "end")
				this->handleElem(child, manager, &Map::addEnd);
			else if (name == "randomMonster")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomMonster);
			else if (name == "mazeMonster")
				this->handleRandomElem(child, manager, &MonsterGenerator::addMazeMonster);
			else if (name == "randomBoss")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomBoss);
			else if (name == "randomWall")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomWall);
			else if (name == "randomHWall")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomHWall);
			else if (name == "randomVWall")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomVWall);
			else if (name == "randomBreakableWall")
				this->handleRandomElem(child, manager, &MonsterGenerator::addRandomBreakableWall);
			else if (name == "squadSound")
				this->handleRandomElem(child, manager, &MonsterGenerator::addSquadSound);
			else if (name == "bossSound")
				this->handleRandomElem(child, manager, &MonsterGenerator::addBossSound);
		}
	}
	_current = 0;
}

void    MapProvider::handleElem(TiXmlNode *parent, Core::ResourceManager &, void (Map::*func)(std::string const &name, size_t, size_t, int, int, bool, bool, int, size_t))
{
	std::string     name, monstername;
	size_t          y = 0, x = 0, ry = 0;
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
		else if (name == "ry")
			ry = Net::Converter::toInt<size_t>(attrib->Value());
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
	  (_current->*func)(monstername, x, y, vx, vy, scrollable, pause, spawnY, ry);
}

void	MapProvider::handleRandomElem(TiXmlNode *parent, Core::ResourceManager &, void (MonsterGenerator::*func)(std::string const &name, bool scrollable, size_t level, int, int, int, int))
{
	std::string     name, monstername;
	bool			scrollable = true;
	size_t			level = 1;
	int				xmin = 0, xmax = 1280;
	int				ymin = 0, ymax = 780;

	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "name")
			monstername = attrib->Value();
		else if (name == "scrollable" && attrib->Value() == "false")
			scrollable = false;
		else if (name == "level")
			level = Net::Converter::toInt<size_t>(attrib->Value());
		else if (name == "xmin")
			xmin = Net::Converter::toInt<int>(attrib->Value());
		else if (name == "xmax")
			xmax = Net::Converter::toInt<int>(attrib->Value());
		else if (name == "ymin")
			ymin = Net::Converter::toInt<int>(attrib->Value());
		else if (name == "ymax")
			ymax = Net::Converter::toInt<int>(attrib->Value());
	}
	MonsterGenerator *gen;
	if (!monstername.empty() && (gen = dynamic_cast<MonsterGenerator *>(_current)))
	  (gen->*func)(monstername, scrollable, level, xmin, xmax, ymin, ymax);
}
