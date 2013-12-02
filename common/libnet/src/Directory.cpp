#include "Directory.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

NET_USE_NAMESPACE

void		Directory::create(std::string const &directory)
{
	std::string		tmp;
	size_t			pos;
	size_t			mempos = 0;
	bool			ret;

	while (mempos < directory.size())
	{
		pos = directory.find('/', mempos);
		if (pos == std::string::npos)
			pos = directory.size();
		else
			pos++;
		tmp += directory.substr(mempos, pos - mempos);
		mempos = pos;
		#ifdef _WIN32
			ret = ::CreateDirectory(tmp.c_str(), NULL);
		#else
			ret = ::mkdir(tmp.c_str(), 0755) == 0;
		#endif
	}
}
