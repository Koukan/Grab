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
    }
	CoreFont *font = this->addFont(fontName, fontFile, fontSize);
	if (font)
	{
		this->XMLProvider::addResource(fontName, *font, manager);
	}
}
