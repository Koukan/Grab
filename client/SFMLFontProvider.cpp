#include "SFMLFontProvider.hpp"

SFMLFontProvider::SFMLFontProvider()
{
}

SFMLFontProvider::~SFMLFontProvider()
{
  for (FontMap::iterator it = this->_fonts.begin(); it != this->_fonts.end(); ++it)
    delete it->second;
}

void SFMLFontProvider::addFont(std::string const &fontName, std::string const &fontFile, std::string const &fontSize)
{
  FontMap::const_iterator it = this->_fonts.find(fontName);

  if (it == this->_fonts.end())
    {
      SFMLFont *font = new SFMLFont(fontFile, fontSize);

      this->_fonts.insert(std::pair<std::string const, SFMLFont *>(fontName, font));
    }
}

Font	*SFMLFontProvider::getFont(std::string const &fontName) const
{
  FontMap::const_iterator it = this->_fonts.find(fontName);

  if (it != this->_fonts.end())
    return (new SFMLFont(*(it->second)));
  return (0);
}
