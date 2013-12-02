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

/*!
 \brief Utility to convert primary to std::string and vice-versa
 */
class Converter
{
public:
	/*!
	 \brief Convert a primary type to a std::string 

	 \tparam T Primary type
	 \param value Value to be converted

	 \return a string of the value
	 */
	template <typename T>
	static std::string  toString(T value)
	{
	std::ostringstream     st;

	st << value;
	return (st.str());
	}
	/*!
	 \brief Convert a std::string to a primary type

	 \tparam T Primary type
	 \param str std::string to be converted

	 \return the primary type extracted from the std::string
	 */
	template <typename T>
	static T toInt(const std::string &str)
	{
		if (str.empty())
			return (0);
	std::istringstream	  st(str);
	T			  value;
	st >> value;
	return (value);
	}
};

NET_END_NAMESPACE

#endif /* _CONVERTER_ */
