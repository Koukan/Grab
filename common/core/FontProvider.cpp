#include <string>
#include "FontProvider.hpp"
#include "Converter.hpp"

CORE_USE_NAMESPACE

FontProvider::FontProvider()
  : XMLProvider("font", 2)
{
}

FontProvider::~FontProvider()
{
}

void	FontProvider::handleXML(TiXmlNode *parent, ResourceManager &manager)
{
	std::string		name;
	std::string		fontName;
	std::string		fontFile;
	int r = 255, g = 255, b = 255, a = 255;
	unsigned int	fontSize;

	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
       attrib != 0; attrib = attrib->Next())
    {
		name = attrib->Name();
		if (name == "name")
			fontName = attrib->Value();
		else if (name == "file")
			fontFile = attrib->Value();
		else if (name == "size")
		  fontSize = Net::Converter::toInt<unsigned int>(attrib->Value());
		else if (name == "color")
		{
			this->get3Int(attrib->Value(), ",", r, g, b);
		}
		else if (name == "transparency")
		{
		    a = Net::Converter::toInt<int>(attrib->Value());
		}
    }
	CoreFont *font = this->addFont(fontName, fontFile, fontSize);
	if (font)
	{
		font->setColor(r, g, b);
		font->setTransparency(a);
		this->XMLProvider::addResource(fontName, *font, manager);
	}
}

void		FontProvider::get3Int(std::string const &data, std::string const &sep,
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
