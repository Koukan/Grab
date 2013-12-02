#pragma once

#include "NetDef.hpp"
#include <string>

NET_BEGIN_NAMESPACE

/*!
 \brief Directory class
 */
class NET_DLLREQ Directory
{
public:
	
	/*!
	 \brief Create a directory
	 \param directory path and name of the desired directory
	 */
	static void		create(std::string const &directory);
};

NET_END_NAMESPACE
