#pragma once

#include <string>
#include <map>
#include "XMLProvider.hpp"
#include "Map.hpp"

class	MapProvider : public Core::XMLProvider
{
	public:
			MapProvider();
			virtual ~MapProvider();
			virtual void    handleXML(TiXmlNode *, Core::ResourceManager &);

	private:
			void    		handleEnd(TiXmlNode *, Core::ResourceManager &);
			void    		handleMonster(TiXmlNode *, Core::ResourceManager &);
			void    		handleDeco(TiXmlNode *, Core::ResourceManager &);
			void    		handleSound(TiXmlNode *, Core::ResourceManager &);
  void    		handleElem(TiXmlNode *, Core::ResourceManager &, void (Map::*func)(std::string const &, size_t, size_t, int, int, bool, bool, int));

			Map			*_current;
};
