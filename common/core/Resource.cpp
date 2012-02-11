#include "Resource.hpp"
#include "XMLProvider.hpp"
#include <iostream>

Resource::Resource()
	: _resourceId(*new uint32_t(0)), _resourceType(0), _resourceProvider(0),
	  _resourceName(*new std::string), _use(*new uint32_t(1))
{
}

Resource::Resource(Resource const &other)
	: _resourceId(other._resourceId), _resourceType(other._resourceType),
	 _resourceProvider(other._resourceProvider),
	 _resourceName(other._resourceName), _use(other._use)
{
	++this->_use;
}

Resource::~Resource()
{
	if (this->_use != 0)
		--this->_use;
	if (this->_resourceProvider && this->_use == 0)
		this->_resourceProvider->deleteResource(this->_resourceName);
}

void		Resource::setResourceId(uint32_t id)
{
	if (this->_resourceProvider)
		this->_resourceProvider->changeId(*this, id);
	else
		this->_resourceId = id;
}

void		Resource::setResourceName(std::string const &name)
{
	if (this->_resourceProvider)
		this->_resourceProvider->changeName(*this, name);
	else
		this->_resourceName = name;
}

uint32_t	Resource::getResourceId() const
{
	return this->_resourceId;
}

uint32_t	Resource::getResourceType() const
{
	return this->_resourceType;
}

std::string const	&Resource::getResourceName() const
{
	return this->_resourceName;
}

XMLProvider	*Resource::getResourceProvider() const
{
	return this->_resourceProvider;
}

void		Resource::addUse() const
{
	++this->_use;
}

void		Resource::removeUse() const
{
	--this->_use;
	if (this->_use == 0)
		delete this;
}

uint32_t	Resource::getUse() const
{
	return this->_use;
}
