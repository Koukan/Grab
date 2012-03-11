#pragma once

#include <map>
#include <string>
#include "tinyxml.h"
#include "ResourceManager.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ XMLProvider
{
public:
	XMLProvider(std::string const &handledTag, uint8_t type);
	virtual ~XMLProvider();
	virtual void	init();
	virtual void	handleXML(TiXmlNode *, ResourceManager &) = 0;
	void			addResource(std::string const &name, Resource &resource);
	void			addResource(std::string const &name, Resource &resource, ResourceManager &manager);
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
	uint8_t const		type;

protected:
	typedef	std::map<std::string const, Resource*>	ResourceMap;
	typedef	std::map<uint8_t, Resource*>			IdMap;

	uint32_t			_id;
	ResourceMap			_resources;
	IdMap				_ids;
};

CORE_END_NAMESPACE
