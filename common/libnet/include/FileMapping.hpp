#pragma once

#include <string>
#include <tuple>
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief FileMapping utility 
 */
class NET_DLLREQ	FileMapping
{
public:
	/*!
	 \brief Map the file in memory
	 \param path path of the file to map
	 \param offset offset in the file, can be 0
	 \param size a size to map, if zero map the whole file

	 \return the pointer in the memory and the size of mapped are
	 */
	static std::tuple<void *, std::size_t> map(std::string const &path, std::size_t offset = 0, std::size_t size = 0);
	/*!
	 \brief unmap the file

	 \param addr the pointer returned by the function map
	 */
	static void unmap(void *addr);
};

NET_END_NAMESPACE
