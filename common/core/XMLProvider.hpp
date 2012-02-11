#pragma once

#include <map>
#include <string>
#include "tinyxml.h"
#include "ResourceManager.hpp"

class XMLProvider
{
public:
	XMLProvider(std::string const &handledTag, uint32_t type);
	virtual ~XMLProvider();
	virtual void	init();
	virtual void	handleXML(TiXmlNode *, ResourceManager &) = 0;
	void			addResource(std::string const &name, Resource &resource, ResourceManager &manager);
	virtual void	addResource(Resource&, ResourceManager&);
	virtual void	deleteResource(std::string const &name);

	// setter
	bool			setId(uint32_t id);
	void			changeId(Resource &resource, uint32_t id);
	void			changeId(std::string const &name, uint32_t	id);
	void			changeId(uint32_t oldId, uint32_t newId);
	void			changeName(Resource &resource, std::string const &name);
	void			changeName(std::string const &oldName, std::string const &newName);
	void			changeName(uint32_t id, std::string const &name);


	// getter
	Resource		*getResource(std::string const &name) const;
	Resource		*getResource(uint32_t id) const;

	std::string const	handledTag;
	uint32_t const		type;

protected:
	typedef	std::map<std::string const, Resource*>	ResourceMap;
	typedef	std::map<uint32_t, Resource*>			IdMap;

	uint32_t			_id;
	ResourceMap			_resources;
	IdMap				_ids;
};
