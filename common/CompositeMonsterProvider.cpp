#include "CompositeMonsterProvider.hpp"
#include "CompositeMonster.hpp"
#include "Converter.hpp"

CompositeMonsterProvider::CompositeMonsterProvider() : XMLProvider("compositemonster", 6)
{
}

CompositeMonsterProvider::~CompositeMonsterProvider()
{
}

void    CompositeMonsterProvider::handleXML(TiXmlNode *parent, Core::ResourceManager &manager)
{
	std::string		name, bossname;

	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "bulletml")
			this->_bulletml = attrib->Value();
		else if (name == "name")
			bossname = attrib->Value();
	}
	CompositeMonster *mon = new CompositeMonster(_bulletml);
	for (TiXmlNode *child = parent->FirstChild(); child;
		 child = child->NextSibling())
	{
		if (child->Type() != TiXmlNode::ELEMENT)
			continue ;
		CompositeMonsterProvider::monster tmp;
		tmp.x = 0;
		tmp.y = 0;
		for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(child)->FirstAttribute(); attrib != 0; attrib = attrib->Next())
		{
			name = attrib->Name();
			if (name == "bulletml")
				tmp.bulletmlscript = attrib->Value();
			else if (name == "name")
				tmp.name = attrib->Value();
			else if (name == "x")
				tmp.x = Net::Converter::toInt<int>(attrib->Value());
			else if (name == "y")
				tmp.y = Net::Converter::toInt<int>(attrib->Value());
			else if (name == "depends")
				{
					size_t index = 0;
					size_t pos;
					std::string	str(attrib->Value());
					while ((pos = str.find(',', index)) != std::string::npos)
					{
						tmp.depends.push_back(str.substr(index, pos));
						index = pos + 1;
					}
					tmp.depends.push_back(str.substr(index));
				}
		}
		mon->addMonster(tmp);
	}
	this->addResource(bossname, *mon, manager);
}

