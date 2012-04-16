#pragma once

#include <string>
#include <map>
#include "XMLProvider.hpp"

class	CompositeMonsterProvider : public Core::XMLProvider
{
	public:
			CompositeMonsterProvider();
			virtual ~CompositeMonsterProvider();
			virtual void    handleXML(TiXmlNode *, Core::ResourceManager &);
			struct monster
			{
				int			x;
				int			y;
				std::string	bulletmlscript;
				std::string	name;
				std::list<std::string>	depends;
			};

	private:
			std::string     	_bulletml;
};
