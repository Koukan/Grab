/*
** Converter for nibbler in /home/snap/projects/nibbler
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Mon 14 Mar 2011 07:29:46 PM CET botton vivien
** Last update Mon 14 Mar 2011 07:29:46 PM CET botton vivien
*/

#ifndef _CONVERTER_
#define _CONVERTER_

#include <string>
#include <sstream>
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

class Converter
{
public:
	template <typename T>
	static std::string  toString(T value)
	{
	std::ostringstream     st;

	st << value;
	return (st.str());
	}
	template <typename T>
	static T toInt(const std::string &str)
	{
	std::istringstream	  st(str);
	T			  value;
	st >> value;
	return (value);
	}
};

NET_END_NAMESPACE

#endif /* _CONVERTER_ */
