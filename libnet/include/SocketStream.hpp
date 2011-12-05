/*
 * SocketStream.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#ifndef HandleSTREAM_HPP_
#define HandleSTREAM_HPP_

#include "SocketIO.hpp"

class SocketStream : public SocketIO
{
public:
	SocketStream();
	~SocketStream();

	int		shutdown(int flags = SHUT_RDWR);

};
#endif /* HandleSTREAM_HPP_ */
