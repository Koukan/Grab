#include "FontProvider.hpp"
#include <string>

FontProvider::FontProvider()
  : XMLProvider("font")
{
}

FontProvider::~FontProvider()
{
}

void	FontProvider::handleXML(TiXmlNode *parent)
{
  std::string path;
  std::string name;
  std::string fontName;
  std::string fontFile;
  std::string fontSize;

  for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
       attrib != 0; attrib = attrib->Next())
    {
      name = attrib->Name();
      if (name == "name")
	fontName = attrib->Value();
      else if (name == "file")
	fontFile = attrib->Value();
      else if (name == "size")
	fontSize = attrib->Value();
    }
  this->addFont(fontName, fontFile, fontSize);
}
