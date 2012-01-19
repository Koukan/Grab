/*
 * Error.hpp
 *
 *  Created on: Dec 8, 2011
 *      Author: snap
 */

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include "NetDef.hpp"

#include <string>

NET_BEGIN_NAMESPACE

std::string		getLastError();
void			printLastError();

NET_END_NAMESPACE

#endif /* ERROR_HPP_ */
