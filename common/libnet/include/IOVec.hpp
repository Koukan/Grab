/*
 * IOVec.hpp
 *
 *  Created on: Nov 4, 2011
 *      Author: snap
 */

#ifndef IOVEC_HPP_
#define IOVEC_HPP_

#include "NetDef.hpp"
#include "network.h"
#include <string>
#include <vector>

NET_BEGIN_NAMESPACE

class NET_DLLREQ IOVec
{
public:
	IOVec();
	~IOVec();

	void	clean();
	size_t	getSize();
	void	addBuffer(char *buff, size_t size);
	struct iovec *getPtr();

private:
	std::vector<struct iovec>	_vec;

};

NET_END_NAMESPACE

#endif /* IOVEC_HPP_ */
