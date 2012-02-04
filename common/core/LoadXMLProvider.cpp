#include "LoadXMLProvider.hpp"
#include "GlobalResourceManager.hpp"


LoadXMLProvider::LoadXMLProvider()
	: XMLProvider("load", 0)
{
}

LoadXMLProvider::~LoadXMLProvider()
{
}

void		LoadXMLProvider::handleXML(TiXmlNode *node, ResourceManager &manager)
{
	std::string		name;

	for (TiXmlAttribute *attrib = static_cast<TiXmlElement*>(node)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "xml")
			GlobalResourceManager::get().load(attrib->Value(), manager);
	}
}
