#pragma once

#include "Font.hpp"
#include "XMLProvider.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ FontProvider : public XMLProvider
{
public:
  FontProvider();
  virtual ~FontProvider();
  virtual CoreFont	*addFont(std::string const &, std::string const &, unsigned int) = 0;

  virtual void		handleXML(TiXmlNode *node, ResourceManager &);
};

CORE_END_NAMESPACE
