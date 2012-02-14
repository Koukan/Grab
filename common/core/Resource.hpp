#pragma once

#include <stdint.h>
#include <string>

class XMLProvider;

class Resource
{
  public:
	Resource();
	Resource(Resource const &other);
    virtual ~Resource();

	virtual Resource	*clone() const = 0;

	// setter
	void				setResourceId(uint32_t id);
	void				setResourceName(std::string const &name);

	// getter
	uint32_t			getResourceId() const;
	uint32_t			getResourceType() const;
	std::string const	&getResourceName() const;
	XMLProvider			*getResourceProvider() const;

	void				addUse() const;
	void				removeUse() const;
	uint32_t			getUse() const;

  private:
	uint32_t		&_resourceId;
	uint8_t			_resourceType;
	XMLProvider		*_resourceProvider;
	std::string		&_resourceName;
	uint32_t		&_use;
	friend class	XMLProvider;
};
