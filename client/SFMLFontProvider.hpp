#pragma once

#include "FontProvider.hpp"
#include "SFMLFont.hpp"
#include <map>

class SFMLFontProvider : public FontProvider
{
public:
	SFMLFontProvider();
	~SFMLFontProvider();

	virtual CoreFont	*addFont(std::string const &fontName, std::string const &fontFile, unsigned int fontSize);
	virtual Resource	*getResource(std::string const &fontName) const;
	virtual void		deleteResource(std::string const &name);

private:
	typedef std::map<std::string const, SFMLFont *>	FontMap;

	FontMap _fonts;
};
