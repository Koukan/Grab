#include <string>
#include "SoundProvider.hpp"
#include "Converter.hpp"

CORE_USE_NAMESPACE

SoundProvider::SoundProvider()
  : XMLProvider("sound", 4)
{
}

SoundProvider::~SoundProvider()
{
}

void	SoundProvider::handleXML(TiXmlNode *parent, ResourceManager &manager)
{
	std::string		name;
	std::string		soundName;
	std::string		soundFile;
	bool			loop = false;

	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
       attrib != 0; attrib = attrib->Next())
    {
		name = attrib->Name();
		if (name == "name")
			soundName = attrib->Value();
		else if (name == "file")
			soundFile = attrib->Value();
		else if (name == "loop" && attrib->Value() == "true")
			loop = true;
    }
	Sound *sound = this->addSound(soundName, soundFile);
	if (sound)
	{
		sound->setLoop(loop);
		this->XMLProvider::addResource(soundName, *sound, manager);
	}
}

