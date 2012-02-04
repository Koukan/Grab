#include "SFMLFontProvider.hpp"
#include <iostream>

SFMLFontProvider::SFMLFontProvider()
{
}

SFMLFontProvider::~SFMLFontProvider()
{
}

CoreFont	*SFMLFontProvider::addFont(std::string const &fontName, std::string const &fontFile, unsigned int fontSize)
{
	ResourceMap::const_iterator it = this->_resources.find(fontName);

	if (it == this->_resources.end())
		return new SFMLFont(fontFile, fontSize);
	else
		return static_cast<CoreFont*>(it->second);
}
