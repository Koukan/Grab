#include "LoadXMLProvider.hpp"
#include "ResourceManager.hpp"

LoadXMLProvider::LoadXMLProvider(ResourceManager &manager)
	: XMLProvider("load"), _manager(manager)
{
}

LoadXMLProvider::~LoadXMLProvider()
{
}

void		LoadXMLProvider::handleXML(TiXmlNode *node)
{
	std::string		name;
	std::string		bulletparser;
	std::string		bulletname;

	for (TiXmlAttribute *attrib = static_cast<TiXmlElement*>(node)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "xml")
			this->_manager.load(attrib->Value());
		else if (name == "bulletml")
			bulletparser = attrib->Value();
		else if (name == "name")
			bulletname = attrib->Value();
	}
	if (!bulletparser.empty() && !bulletname.empty())
		this->_manager.addBulletParser(bulletparser, bulletname);
}
