#pragma once

#include "FontProvider.hpp"
#include "SFMLFont.hpp"
#include <map>

class SFMLFontProvider : public FontProvider
{
public:
  SFMLFontProvider();
  ~SFMLFontProvider();

  virtual void	addFont(std::string const &fontName, std::string const &fontFile, std::string const &fontSize);
  virtual Font	*getFont(std::string const &fontName) const;

  typedef std::map<std::string const, SFMLFont *>	FontMap;

private:
  FontMap _fonts;
};
