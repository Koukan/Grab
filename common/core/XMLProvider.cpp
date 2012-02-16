#include "XMLProvider.hpp"

XMLProvider::XMLProvider(std::string const &handledTag, uint8_t type)
  : handledTag(handledTag), type(type), _id(1)
{
}

XMLProvider::~XMLProvider()
{
}

void		XMLProvider::init()
{
}

void		XMLProvider::deleteResource(std::string const &name)
{
	ResourceMap::iterator	it = this->_resources.find(name);

	if (it != this->_resources.end())
	{
		this->_ids.erase(it->second->getResourceId());
		this->_resources.erase(it);
	}
}

void		XMLProvider::addResource(std::string const &name,
				Resource &resource, ResourceManager &manager)
{
	uint32_t		id = this->_id++;

	if (!resource._resourceProvider)
	{
		resource._resourceId = id;
		resource._resourceName = name;
		resource._resourceType = this->type;
		resource._resourceProvider = this;
		resource._use--;
		this->_resources[name] = &resource;
		this->_ids[id] = &resource;
	}
	manager.addResource(resource);
}

bool		XMLProvider::setId(uint32_t id)
{
	if (this->_id < id)
	{
		this->_id = id;
		return true;
	}
	return false;
}

void		XMLProvider::changeId(Resource &resource, uint32_t id)
{
	this->changeId(resource._resourceId, id);
}

void		XMLProvider::changeId(std::string const &name, uint32_t id)
{
	ResourceMap::iterator	it = this->_resources.find(name);

	if (it != this->_resources.end())
		this->changeId(it->second->_resourceId, id);
}

void		XMLProvider::changeId(uint32_t oldId, uint32_t newId)
{
	IdMap::iterator		it = this->_ids.find(oldId);

	if (it != this->_ids.end())
	{
		Resource	*res = it->second;
		this->_ids.erase(it);
		res->_resourceId = newId;
		this->_ids[newId] = res;
	}
}

void		XMLProvider::changeName(Resource &resource, std::string const &name)
{
	this->changeName(resource._resourceName, name);
}

void		XMLProvider::changeName(std::string const &oldName,
									std::string const &newName)
{
	ResourceMap::iterator	it = this->_resources.find(oldName);

	if (it != this->_resources.end())
	{
		Resource		*res = it->second;
		this->_resources.erase(it);
		res->_resourceName = newName;
		this->_resources[newName] = res;
	}
}

void		XMLProvider::changeName(uint32_t id, std::string const &name)
{
	IdMap::iterator		it = this->_ids.find(id);

	if (it != this->_ids.end())
		this->changeName(it->second->_resourceName, name);
}

Resource	*XMLProvider::getResource(std::string const &name) const
{
	ResourceMap::const_iterator it = this->_resources.find(name);

	if (it != this->_resources.end())
		return it->second->clone();
	return 0;
}

Resource	*XMLProvider::getResource(uint32_t id) const
{
	IdMap::const_iterator		it = this->_ids.find(id);

	if (it != this->_ids.end())
		return it->second->clone();
	return 0;
}
