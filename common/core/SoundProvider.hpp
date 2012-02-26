#pragma once

#include "Sound.hpp"
#include "XMLProvider.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ SoundProvider : public XMLProvider
{
public:
  SoundProvider();
  virtual ~SoundProvider();
  virtual Sound		*addSound(std::string const &soundname, std::string const &sounfile) = 0;

  virtual void		handleXML(TiXmlNode *node, ResourceManager &);

private:
};

CORE_END_NAMESPACE
