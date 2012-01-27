#include <fstream>
#include "File.hpp"
#include "md5.h"

File::File()
{
}

File::~File()
{
}

bool		File::load(std::string const &path)
{
	std::ifstream	file(path.c_str());
	char			*buffer;
	size_t			size = 1300;
	md5_state_t		pms;
	char			md5[16];

	if (file)
	{
		::md5_init(&pms);
		while (!file.eof())
		{
			buffer = new char[size];
			file.read(buffer, size);
			if (file.eof())
				size = file.gcount();
			::md5_append(&pms, reinterpret_cast<md5_byte_t*>(buffer), size);
			this->_list.push_back(new Net::DataBlock(buffer, size));
		}
		::md5_finish(&pms, reinterpret_cast<md5_byte_t*>(md5));
		this->_md5.assign(md5, 16);
		this->_path = path;
		file.close();
	}
	return false;
}
