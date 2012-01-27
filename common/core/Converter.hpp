#ifndef _CONVERTER_
#define _CONVERTER_

#include <string>
#include <memory>
#include <vector>
#include <sstream>

class Converter
{
public:
	template <typename T>
	static std::string  toString(T value)
	{
		std::ostringstream	st;

		st << value;
		return (st.str());
	}
	template <typename T>
	static T toInt(const std::string &str)
	{
		std::istringstream	st(str);
		T					value;
		st >> value;
		return (value);
	}
};


#endif /* _CONVERTER_ */
