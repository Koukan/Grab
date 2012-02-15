#pragma once

#include "FontProvider.hpp"
#include "SFMLFont.hpp"
#include <map>

class SFMLFontProvider : public Core::FontProvider
{
public:
	SFMLFontProvider();
	virtual ~SFMLFontProvider();

  virtual Core::CoreFont	*addFont(std::string const &fontName, std::string const &fontFile, unsigned int fontSize);
};
