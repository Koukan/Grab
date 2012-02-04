#pragma once

#include <string>
#include "tinyxml.h"
#include "ResourceManager.hpp"

class XMLProvider
{
public:
	XMLProvider(std::string const &handledTag);
	virtual ~XMLProvider(){}
	virtual void		handleXML(TiXmlNode *, ResourceManager &) = 0;
	virtual Resource	*getResource(std::string const &name) const;
	virtual void		deleteResource(std::string const &name);

	bool				setId(uint32_t id);
	std::string const	&getHandledTag() const;

protected:
	uint32_t		_id;

private:
	std::string		_handledTag;
};
