#pragma once

#include "FontProvider.hpp"
#include "SFMLFont.hpp"
#include <map>

class SFMLFontProvider : public FontProvider
{
public:
	SFMLFontProvider();
	virtual ~SFMLFontProvider();

	virtual CoreFont	*addFont(std::string const &fontName, std::string const &fontFile, unsigned int fontSize);
};
