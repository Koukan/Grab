#include <string>
#include "FontProvider.hpp"
#include "Converter.hpp"

FontProvider::FontProvider()
  : XMLProvider("font")
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
			fontSize = Converter::toInt<unsigned int>(attrib->Value());
    }
	CoreFont *font = this->addFont(fontName, fontFile, fontSize);
	if (font)
	{
		font->setResourceType(2);
		font->setResourceId(this->_id++);
		font->setResourceName(fontName);
		font->setResourceProvider(this);
		manager.addFont(*font);
	}
}
