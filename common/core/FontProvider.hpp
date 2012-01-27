#pragma once

#include "Font.hpp"
#include "XMLProvider.hpp"

class FontProvider : public XMLProvider
{
public:
  FontProvider();
  virtual ~FontProvider();
  virtual void	addFont(std::string const &, std::string const &, std::string const &) = 0;
  virtual Font	*getFont(std::string const &) const = 0;
  
  virtual void		handleXML(TiXmlNode *node);
};
